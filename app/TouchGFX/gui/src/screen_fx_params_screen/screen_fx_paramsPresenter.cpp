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

void screen_fx_paramsPresenter::set_sliders_value(uint32_t* val)
{
	view.set_sliders_value(val);
}


