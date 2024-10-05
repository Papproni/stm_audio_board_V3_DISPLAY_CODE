#include <gui/screen_edit_screen/screen_editView.hpp>
#include <gui/screen_edit_screen/screen_editPresenter.hpp>

screen_editPresenter::screen_editPresenter(screen_editView& v)
    : view(v)
{

}

void screen_editPresenter::activate()
{

}

void screen_editPresenter::deactivate()
{

}

void screen_editPresenter::update_screen()
{
	view.update_screen();
}
