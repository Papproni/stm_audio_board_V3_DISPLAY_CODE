#include <gui/screen_tuning_screen/screen_tuningView.hpp>
#include <gui/screen_tuning_screen/screen_tuningPresenter.hpp>

screen_tuningPresenter::screen_tuningPresenter(screen_tuningView& v)
    : view(v)
{

}

void screen_tuningPresenter::activate()
{

}

void screen_tuningPresenter::deactivate()
{
}

void screen_tuningPresenter::update_screen()
{
    #ifndef SIMULATOR
        model->read_tuner_data();
        view.tuner_un = model->get_tuner_data();
    #endif
    view.update_screen();
}
