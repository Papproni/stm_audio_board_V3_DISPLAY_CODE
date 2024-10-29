#include <gui/screen_loop_screen/screen_loopView.hpp>
#include <gui/screen_loop_screen/screen_loopPresenter.hpp>

screen_loopPresenter::screen_loopPresenter(screen_loopView& v)
    : view(v)
{

}

void screen_loopPresenter::activate()
{
#ifndef  SIMULATOR
	view.loop_num_un = model->get_loop_data(model->get_current_fx_slot_num());
#endif
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
#endif // ! SIMULATOR
	view.update_screen();
}

