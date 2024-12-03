#include <gui/containers/template_fx_param.hpp>

template_fx_param::template_fx_param()
{

}

void template_fx_param::initialize()
{
    template_fx_paramBase::initialize();

    this->potmeter_scale_value 	= -280;
	this->potmeter_min_value 	= -140;
	this->potmeter_offset_value = 140;
	this->adc_raw_max_value		= 65535;
    this->delta                 = 4;
}


uint8_t template_fx_param::convert_adc_to_param_values(uint32_t val)
{
	return UINT8_MAX-(double)val/(double)this->adc_raw_max_value*UINT8_MAX;
}

int template_fx_param::convert_adc_to_pot_values(uint32_t val)
{
	return (double)val/(double)this->adc_raw_max_value*this->potmeter_scale_value+this->potmeter_offset_value;
}

int template_fx_param::convert_uint8t_to_pot_values(uint8_t val)
{
	return (double)val/(double)UINT8_MAX*this->potmeter_scale_value+this->potmeter_offset_value;
}


// returns 0 if no change is detected
// returns 1 if change should be sent to the DSP module
uint8_t template_fx_param::update_potmeter(uint32_t new_value){
    potmeter.invalidate();

    int value_converted = convert_adc_to_pot_values(new_value);
    if(abs(value_converted-last_value_u8)>delta){
        potmeter.setArc(this->potmeter_min_value, value_converted);
        potmeter.invalidate();
        last_value_u8 = value_converted;
        this->param_value_u8 = convert_adc_to_param_values(new_value);
        return 1;
    }
    return 0;
}

// returns 0 if no change is detected
// returns 1 if change should be sent to the DSP module
uint8_t template_fx_param::update_btn(){
    uint8_t current_state = this->btn.getState();
    if(current_state != this->last_value_u8){
        this->last_value_u8  = current_state;
        this->param_value_u8 = current_state;
        return 1;
    }
    // TODO
    return 0;
}


// returns 0 if no change is detected
// returns 1 if change should be sent to the DSP module
uint8_t template_fx_param::update_ui(uint32_t value){
    switch (this->paramtype)
    {
    case PARAM_TYPE_POT:
        return this->update_potmeter(value);
        break;
    case PARAM_TYPE_BTN:
        return this->update_btn();
        break;
    default:
        break;
    }
    return 0;
}

void template_fx_param::init_ui(uint8_t value_u8){
    switch (this->paramtype)
    {
    case PARAM_TYPE_POT:
        this->potmeter.setVisible(true);
        potmeter.invalidate();
        potmeter.setArc(this->potmeter_min_value, convert_uint8t_to_pot_values(value_u8));
        potmeter.invalidate();
        break;
    case PARAM_TYPE_BTN:
        this->btn.setVisible(true);
        
        this->btn.forceState(1 == value_u8);
        break;
    default:
        break;
    }
}

void template_fx_param::init_parameter(char* char_ptr, uint8_t len,param_type_ten type,uint8_t value_u8){
    if(PARAM_TYPE_POT != type && PARAM_TYPE_BTN != type){
        return;
    }
    
    Unicode::strncpy(param_nameBuffer,char_ptr,len);
    param_name.resizeToCurrentText();
    param_name.setVisible(true);
    param_name.invalidate();

    this->paramtype     = type;
    this->last_value_u8 = value_u8;

    this->init_ui(value_u8);
}

// GETTERS 
param_type_ten template_fx_param::get_param_type(){
    return this->paramtype;
}

uint8_t template_fx_param::get_param_value(){
    return this->param_value_u8;
}

