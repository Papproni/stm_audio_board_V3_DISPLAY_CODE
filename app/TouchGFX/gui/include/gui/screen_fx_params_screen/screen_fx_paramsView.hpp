#ifndef SCREEN_FX_PARAMSVIEW_HPP
#define SCREEN_FX_PARAMSVIEW_HPP

#include <gui_generated/screen_fx_params_screen/screen_fx_paramsViewBase.hpp>
#include <gui/screen_fx_params_screen/screen_fx_paramsPresenter.hpp>

class screen_fx_paramsView : public screen_fx_paramsViewBase
{
public:
    screen_fx_paramsView();
    virtual ~screen_fx_paramsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    int potmeter_scale_value;
    int potmeter_offset_value;
    int potmeter_min_value;
    int adc_raw_max_value;

    virtual void set_sliders_value(uint32_t* val);

protected:
    int convert_adc_to_pot_values(int val);
};

#endif // SCREEN_FX_PARAMSVIEW_HPP
