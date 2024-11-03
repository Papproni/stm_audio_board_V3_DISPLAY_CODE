#ifndef SCREEN_FX_PARAMSVIEW_HPP
#define SCREEN_FX_PARAMSVIEW_HPP

#include <gui_generated/screen_fx_params_screen/screen_fx_paramsViewBase.hpp>
#include <gui/screen_fx_params_screen/screen_fx_paramsPresenter.hpp>

#define NUM_OF_ROWS 2
#define NUM_OF_COLLUMS 3
#define NUM_OF_PARAMS_PER_PAGE NUM_OF_COLLUMS *NUM_OF_ROWS
#define NUM_OF_PARAM_PAGES 2


#define START_LOC 40
#define ROW_HEIGHT 90
#define COLLUM_WIDTH 80

// #include <template_fx_param_btn.hpp>
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

    uint8_t parameter_positions_au8[NUM_OF_PARAMS_PER_PAGE][2];

    template_fx_param *fx_controls_p[12];

    virtual void set_sliders_value(uint32_t *val);
    uint32_t *adc_vals_ptr;
#ifndef SIMULATOR
    sab_fx_param_tun fx_params_tun[12];
#endif
    virtual void update_screen();

protected:
    int convert_adc_to_pot_values(int val);
};

#endif // SCREEN_FX_PARAMSVIEW_HPP
