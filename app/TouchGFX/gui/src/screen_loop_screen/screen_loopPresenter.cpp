#include <gui/screen_loop_screen/screen_loopView.hpp>
#include <gui/screen_loop_screen/screen_loopPresenter.hpp>

screen_loopPresenter::screen_loopPresenter(screen_loopView& v)
    : view(v)
{

}

void screen_loopPresenter::activate()
{
#ifndef  SIMULATOR
	// model->read_loop_data(model->get_current_loop_num());
	// view.loop_num_un = model->get_loop_data(model->get_current_fx_slot_num());
#endif
#ifdef SIMULATOR
	
#endif // DEBUG
	view.inited = 0;
	view.state = NORMAL;
	

}

void screen_loopPresenter::deactivate()
{

}

void screen_loopPresenter::setFXname(char* data)
{
	model->setFXname(data);
}

void screen_loopPresenter::update_screen()
{
#ifndef  SIMULATOR
	model->read_loop_data(model->get_current_loop_num());
	view.loop_num_un = model->get_loop_data(model->get_current_loop_num());
	model->read_preset_data();
	view.preset_data_un = model->get_preset_data();
#endif // ! SIMULATOR
	view.update_screen();
}

void screen_loopPresenter::set_loop_data()
{
#ifndef  SIMULATOR
	// model->read_loop_data(model->get_current_loop_num());
	model->set_loop_data(&view.loop_num_un);
#endif // ! SIMULATOR
}
#ifndef  SIMULATOR
void screen_loopPresenter::add_fx(fx_slots_ten slot){
	model->set_current_fx_slot_num(slot);
}

// Swap all 12 FX parameter values of two slots in the current loop.
// Must be called BEFORE set_loop_data() when moving an effect: the DSP ties
// parameters to slot position when it rebuilds the chain after a name change,
// so pre-swapping the blocks makes each effect keep its own parameters at its
// new position.
void screen_loopPresenter::swap_slot_fx_params(uint8_t slot_a_u8, uint8_t slot_b_u8)
{
	uint8_t tmpA[12] = {0};
	uint8_t tmpB[12] = {0};

	// Read all 12 parameters of slot A
	model->set_current_fx_slot_num(slot_a_u8);
	model->set_current_fx();
	for (uint8_t i = 1; i <= 12; i++)
	{
		model->read_fx_param(i);
		tmpA[i - 1] = model->get_fx_param(i - 1).value_u8;
	}

	// Read all 12 parameters of slot B
	model->set_current_fx_slot_num(slot_b_u8);
	model->set_current_fx();
	for (uint8_t i = 1; i <= 12; i++)
	{
		model->read_fx_param(i);
		tmpB[i - 1] = model->get_fx_param(i - 1).value_u8;
	}

	// Write B's parameters into slot A, and A's parameters into slot B
	model->set_current_fx_slot_num(slot_a_u8);
	model->set_current_fx();
	for (uint8_t i = 1; i <= 12; i++)
	{
		model->set_fx_param(i, tmpB[i - 1]);
	}

	model->set_current_fx_slot_num(slot_b_u8);
	model->set_current_fx();
	for (uint8_t i = 1; i <= 12; i++)
	{
		model->set_fx_param(i, tmpA[i - 1]);
	}
}
#endif // ! SIMULATOR
