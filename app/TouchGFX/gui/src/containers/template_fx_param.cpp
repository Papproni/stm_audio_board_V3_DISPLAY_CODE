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
	this->adc_raw_max_value		= UINT16_MAX;
    this->delta                 = 4;
}


int template_fx_param::convert_adc_to_pot_values(int val)
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
    uint8_t value_converted = convert_adc_to_pot_values(new_value);
    if(abs(value_converted-last_value_u8)>delta){
        potmeter.setArc(this->potmeter_min_value, value_converted);
        potmeter.invalidate();
        last_value_u8 = value_converted;
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
    if(PARAM_TYPE_UNUSED == type){
        return;
    }

    
    Unicode::strncpy(param_nameBuffer,char_ptr,len);
    param_name.resizeToCurrentText();
    param_name.setVisible(true);
    param_name.invalidate();

    // btn1.forceState(true);
    // touchgfx_printf("%d",btn1.getState());

    this->paramtype     = type;
    this->last_value_u8 = value_u8;

    this->init_ui(value_u8);
}

// GETTERS 
param_type_ten template_fx_param::get_param_type(){
    return this->paramtype;
}

uint8_t template_fx_param::get_param_value(){
    return this->last_value_u8;
}

