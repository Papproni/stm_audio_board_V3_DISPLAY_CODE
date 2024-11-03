#ifndef TEMPLATE_FX_PARAM_HPP
#define TEMPLATE_FX_PARAM_HPP

#include <gui_generated/containers/template_fx_paramBase.hpp>

#ifdef SIMULATOR
typedef enum{
	PARAM_TYPE_UNUSED,
	PARAM_TYPE_POT,
	PARAM_TYPE_BTN
}param_type_ten;
#endif // DEBUG

class template_fx_param : public template_fx_paramBase
{
public:
    template_fx_param();
    virtual ~template_fx_param() {}

    virtual void initialize();


    int potmeter_scale_value;
    int potmeter_offset_value;
    int potmeter_min_value;
    int adc_raw_max_value;
    
    // The current value
    uint8_t last_value_u8;
    uint8_t delta;

    // INIT FUNC
    void init_parameter(char* char_ptr, uint8_t len,param_type_ten type, uint8_t value_u8);
     // UPDATE PARAMETER
    void init_ui(uint8_t value_u8);
    // UPDATE PARAMETER
    uint8_t update_ui(uint32_t new_value);
    
    // GETTERS
    param_type_ten get_param_type();
    uint8_t get_param_value();

protected:
    uint8_t update_potmeter(uint32_t new_value);
    uint8_t update_btn();

    int convert_adc_to_pot_values(int val);
    int convert_uint8t_to_pot_values(uint8_t val);
    param_type_ten paramtype;
};

#endif // TEMPLATE_FX_PARAM_HPP
