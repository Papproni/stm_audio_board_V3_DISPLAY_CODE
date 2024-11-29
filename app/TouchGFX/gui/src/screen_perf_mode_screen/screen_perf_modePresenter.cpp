#include <gui/screen_perf_mode_screen/screen_perf_modeView.hpp>
#include <gui/screen_perf_mode_screen/screen_perf_modePresenter.hpp>

screen_perf_modePresenter::screen_perf_modePresenter(screen_perf_modeView& v)
    : view(v)
{

}

void screen_perf_modePresenter::activate()
{

}

void screen_perf_modePresenter::deactivate()
{

}

void screen_perf_modePresenter::update_screen()
{
    #ifndef SIMULATOR
	model->read_preset_data();
    view.preset_data_un = model->get_preset_data();
    #endif
    view.update_screen();
}
