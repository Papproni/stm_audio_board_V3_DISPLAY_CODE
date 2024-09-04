#include <gui/screen_fx_params_screen/screen_fx_paramsView.hpp>

screen_fx_paramsView::screen_fx_paramsView()
{

}

void screen_fx_paramsView::setupScreen()
{
    screen_fx_paramsViewBase::setupScreen();
}

void screen_fx_paramsView::tearDownScreen()
{
    screen_fx_paramsViewBase::tearDownScreen();

}

void screen_fx_paramsView::set_slider1_value(int val)
{
    ParamSlot1.setArc(-140, val);
    ParamSlot1.invalidate();
}
