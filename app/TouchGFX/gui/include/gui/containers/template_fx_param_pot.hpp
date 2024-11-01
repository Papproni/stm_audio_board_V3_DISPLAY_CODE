#ifndef TEMPLATE_FX_PARAM_POT_HPP
#define TEMPLATE_FX_PARAM_POT_HPP

#include <gui_generated/containers/template_fx_param_potBase.hpp>

class template_fx_param_pot : public template_fx_param_potBase
{
public:
    template_fx_param_pot();
    virtual ~template_fx_param_pot() {}

    virtual void initialize();

    int potmeter_scale_value;
    int potmeter_offset_value;
    int potmeter_min_value;
    int adc_raw_max_value;
    
    uint8_t last_value_u8;
    uint8_t delta;

    int convert_adc_to_pot_values(int val);
    uint8_t update_potmeter(uint32_t new_value);
    void init_potmeter(char* char_ptr, uint8_t len,uint32_t value_u32);
protected:
};

#endif // TEMPLATE_FX_PARAM_POT_HPP
