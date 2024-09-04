#include <gui/screen_fx_params_screen/screen_fx_paramsView.hpp>
#include <gui/screen_fx_params_screen/screen_fx_paramsPresenter.hpp>

screen_fx_paramsPresenter::screen_fx_paramsPresenter(screen_fx_paramsView& v)
    : view(v)
{

}

void screen_fx_paramsPresenter::activate()
{

}

void screen_fx_paramsPresenter::deactivate()
{

}

void screen_fx_paramsPresenter::set_slider1_value(int val)
{
	view.set_slider1_value(val);
}


