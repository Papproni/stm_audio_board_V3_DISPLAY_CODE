#include <gui/containers/template_fx_param_pot.hpp>

#ifdef SIMULATOR
#include <touchgfx/Utils.hpp>
#endif


template_fx_param_pot::template_fx_param_pot()
{
    
}

void template_fx_param_pot::initialize()
{
    template_fx_param_potBase::initialize();

    this->potmeter_scale_value 	= -280;
	this->potmeter_min_value 	= -140;
	this->potmeter_offset_value = 140;
	this->adc_raw_max_value		= 65635;
    this->delta                 = 4;
}

int template_fx_param_pot::convert_adc_to_pot_values(int val)
{
	return (double)val/(double)this->adc_raw_max_value*this->potmeter_scale_value+this->potmeter_offset_value;
}

// returns 0 if no change is detected
// returns 1 if change should be sent to the DSP module
uint8_t template_fx_param_pot::update_potmeter(uint32_t new_value){
    ParamSlot.invalidate();
    ParamSlot.setArc(this->potmeter_min_value, convert_adc_to_pot_values(new_value));
    ParamSlot.invalidate();
    return 0;
}

void template_fx_param_pot::init_potmeter(char* char_ptr, uint8_t len,uint32_t value_u32){
    Unicode::strncpy(param_nameBuffer,char_ptr,len);
    param_name.resizeToCurrentText();
    param_name.invalidate();
}