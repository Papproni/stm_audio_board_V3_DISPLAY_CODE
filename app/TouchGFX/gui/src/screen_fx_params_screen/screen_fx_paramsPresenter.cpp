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

void screen_fx_paramsPresenter::set_fx_on_off(bool is_on){
	#ifndef SIMULATOR
	// On/off is stored per-slot inside the current loop (slotN.fx_state_en).
	// Refresh that loop from the DSP, set the active slot, write the whole loop back.
	uint8_t loopnum_u8 = model->get_current_loop_num();
	model->read_loop_data(loopnum_u8);
	sab_loop_num_tun loop_num_un = model->get_loop_data(loopnum_u8);
	fx_state_ten new_state_en = is_on ? FX_STATE_ON : FX_STATE_OFF;
	switch (model->get_current_fx_slot_num())
	{
	case FX_SLOT1:
		loop_num_un.slot1.fx_state_en = new_state_en;
		break;
	case FX_SLOT2:
		loop_num_un.slot2.fx_state_en = new_state_en;
		break;
	case FX_SLOT3:
		loop_num_un.slot3.fx_state_en = new_state_en;
		break;
	default:
		break;
	}
	model->set_loop_data(&loop_num_un);
	#endif // !SIMULATOR
}

bool screen_fx_paramsPresenter::get_current_fx_on_off(){
	#ifndef SIMULATOR
	uint8_t loopnum_u8 = model->get_current_loop_num();
	model->read_loop_data(loopnum_u8);
	sab_loop_num_tun loop_num_un = model->get_loop_data(loopnum_u8);
	fx_state_ten state_en = FX_STATE_OFF;
	switch (model->get_current_fx_slot_num())
	{
	case FX_SLOT1:
		state_en = loop_num_un.slot1.fx_state_en;
		break;
	case FX_SLOT2:
		state_en = loop_num_un.slot2.fx_state_en;
		break;
	case FX_SLOT3:
		state_en = loop_num_un.slot3.fx_state_en;
		break;
	default:
		break;
	}
	return (state_en == FX_STATE_ON);
	#else
	return false;
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

