#include <gui/screen_loop_screen/screen_loopView.hpp>

screen_loopView::screen_loopView()
{

}

void screen_loopView::setupScreen()
{
    screen_loopViewBase::setupScreen();
}

void screen_loopView::tearDownScreen()
{
    screen_loopViewBase::tearDownScreen();
}




void screen_loopView::update_screen()
{

}

void screen_loopView::btn_slot1_pressed()
{
	char data[20] = "SLOT1";
	presenter->setFXname(data);
	application().gotoscreen_fx_paramsScreenNoTransition();

}

void screen_loopView::btn_slot2_pressed()
{
	char data[20] = "SLOT2";
	presenter->setFXname(data);
	application().gotoscreen_fx_paramsScreenNoTransition();
}

void screen_loopView::btn_slot3_pressed()
{
	char data[20] = "SLOT3";
	presenter->setFXname(data);
	application().gotoscreen_fx_paramsScreenNoTransition();
}
