#include <gui/screen_loop_screen/screen_loopView.hpp>
#include <gui/screen_loop_screen/screen_loopPresenter.hpp>

screen_loopPresenter::screen_loopPresenter(screen_loopView& v)
    : view(v)
{

}

void screen_loopPresenter::activate()
{

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
	view.update_screen();
}

