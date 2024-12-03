#include <gui/screen_info_screen/screen_infoView.hpp>
#include <gui/screen_info_screen/screen_infoPresenter.hpp>

screen_infoPresenter::screen_infoPresenter(screen_infoView& v)
    : view(v)
{

}

void screen_infoPresenter::activate()
{

}

void screen_infoPresenter::deactivate()
{

}

void screen_infoPresenter::update_screen()
{
	view.updatescreen();
}


void screen_infoPresenter::update_DSP(){
    model->set_dsp_fw_update_flg();
}