#include <gui/screen_settings_screen/screen_settingsView.hpp>
#include <gui/screen_settings_screen/screen_settingsPresenter.hpp>

screen_settingsPresenter::screen_settingsPresenter(screen_settingsView& v)
    : view(v)
{

}

void screen_settingsPresenter::activate()
{

}

void screen_settingsPresenter::deactivate()
{

}

void screen_settingsPresenter::save_preset(){
    model->set_save();
}