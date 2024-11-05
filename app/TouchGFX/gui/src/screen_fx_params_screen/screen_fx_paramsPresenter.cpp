#include <gui/screen_fx_params_screen/screen_fx_paramsView.hpp>
#include <gui/screen_fx_params_screen/screen_fx_paramsPresenter.hpp>

screen_fx_paramsPresenter::screen_fx_paramsPresenter(screen_fx_paramsView& v)
    : view(v)
{

}

void screen_fx_paramsPresenter::activate()
{
#ifndef SIMULATOR
	// TODO:
	// send data to change fx params to the current fx!


	view.adc_vals_ptr = model->get_adc_value_ptr();
#endif
}

void screen_fx_paramsPresenter::deactivate()
{

}

void screen_fx_paramsPresenter::get_fx_param_data(){

#ifndef SIMULATOR
	model->set_current_fx();
	for(int i = 1; i<=12; i++){
		model->read_fx_param(i);
		view.fx_params_tun[i-1] = model->get_fx_param(i-1);
	}
#endif
}


void screen_fx_paramsPresenter::getFxname(char* data)
{
	model->getFXname(data);
}

void screen_fx_paramsPresenter::set_fx_param_new_value(uint8_t slotnum_u8, uint8_t new_value_u8){
	#ifndef SIMULATOR
	model->set_fx_param(slotnum_u8,new_value_u8);
	
	#endif // !SIMULATOR
}

void screen_fx_paramsPresenter::update_screen(){
	view.update_screen();
}

