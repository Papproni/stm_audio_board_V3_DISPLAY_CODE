#include <gui/screen_fx_params_screen/screen_fx_paramsView.hpp>
#include <gui/screen_fx_params_screen/screen_fx_paramsPresenter.hpp>

screen_fx_paramsPresenter::screen_fx_paramsPresenter(screen_fx_paramsView& v)
    : view(v), last_preset_major_u8(0xFF), last_preset_minor_u8(0xFF)
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
#ifndef SIMULATOR
	// If the preset number changes while on FX params, go back to the loop screen —
	// a new preset can have a different effect setup than the one being edited.
	model->read_preset_data();
	sab_preset_num_tun pst = model->get_preset_data();
	if (last_preset_major_u8 != 0xFF &&
	    (pst.preset_Major_u8 != last_preset_major_u8 || pst.preset_Minor_u8 != last_preset_minor_u8))
	{
		view.return_to_loop_screen();
		return;
	}
	last_preset_major_u8 = pst.preset_Major_u8;
	last_preset_minor_u8 = pst.preset_Minor_u8;
#endif // ! SIMULATOR
	view.update_screen();
}

