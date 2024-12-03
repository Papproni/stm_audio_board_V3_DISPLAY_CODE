#include <gui/screen_info_screen/screen_infoView.hpp>

screen_infoView::screen_infoView()
{

}

void screen_infoView::setupScreen()
{
    screen_infoViewBase::setupScreen();
}

void screen_infoView::tearDownScreen()
{
    screen_infoViewBase::tearDownScreen();
}


 void screen_infoView::btn_DSP_fw_update_pressed(){
    presenter->update_DSP();
 }
void screen_infoView::updatescreen()
{
	scrollableDeugInfo.invalidate();
}

