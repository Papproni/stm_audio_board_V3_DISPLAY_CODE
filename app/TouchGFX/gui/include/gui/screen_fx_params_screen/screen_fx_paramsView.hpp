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

    virtual void set_slider1_value(int val);
protected:
};

#endif // SCREEN_FX_PARAMSVIEW_HPP
