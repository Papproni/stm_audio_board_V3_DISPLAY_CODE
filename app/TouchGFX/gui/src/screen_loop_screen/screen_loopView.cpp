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



// #define SIMULATOR

void screen_loopView::update_screen()
{
#ifndef SIMULATOR
	if(strcmp(loop_num_un.slot1.name,"NONE")){
		cont_Slot1.setVisible(true);
		Unicode::strncpy(text_FXname_1Buffer,loop_num_un.slot1.name,10);
		box_FX_background_1.setColor(touchgfx::Color::getColorFromRGB(loop_num_un.slot1.color[0], loop_num_un.slot1.color[1], loop_num_un.slot1.color[2]));
		text_FXname_1.resizeToCurrentText();
		text_FXname_1.invalidate();
	}else{
		cont_Slot1.setVisible(false);
	}

	if(strcmp(loop_num_un.slot2.name,"NONE")){
		cont_Slot2.setVisible(true);
	}else{
		cont_Slot2.setVisible(false);
	}
	if(strcmp(loop_num_un.slot3.name,"NONE")){
		cont_Slot3.setVisible(true);
	}else{
		cont_Slot3.setVisible(false);
	}
#endif // !SIMULATOR

#ifdef SIMULATOR

	switch (state)
	{
	case DELETE_FX:
		glow_1.setVisible(true);
		glow_2.setVisible(true);
		glow_3.setVisible(true);

		glow_1.invalidate();
		glow_2.invalidate();
		glow_3.invalidate();
		break;
	
	case NORMAL:
		glow_1.invalidate();
		glow_2.invalidate();
		glow_3.invalidate();

		glow_1.setVisible(false);
		glow_2.setVisible(false);
		glow_3.setVisible(false);

		glow_1.invalidate();
		glow_2.invalidate();
		glow_3.invalidate();
		break;
	default:
		break;
	}

	if(inited == 1){
		return;
	}
	inited = 1;
	cont_Slot1.setVisible(true);
	Unicode::strncpy(text_FXname_1Buffer,"OCTAVE",10);
	box_FX_background_1.setColor(touchgfx::Color::getColorFromRGB(50, 30, 80));
	text_FXname_1.resizeToCurrentText();
	text_FXname_1.invalidate();

	cont_Slot2.setVisible(true);
	Unicode::strncpy(text_FXname_2Buffer,"OVERDRIVE",10);
	box_FX_background_2.setColor(touchgfx::Color::getColorFromRGB(10, 255, 10));
	text_FXname_2.resizeToCurrentText();
	text_FXname_2.invalidate();

	cont_Slot3.setVisible(true);
	Unicode::strncpy(text_FXname_3Buffer,"CHORUS",10);
	box_FX_background_3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 0));
	text_FXname_3.resizeToCurrentText();
	text_FXname_3.invalidate();
#endif // DEBUG
}

void screen_loopView::btn_del_pressed(){
	if(DELETE_FX == state){
		state = NORMAL;
	}else{
		state = DELETE_FX;
	}
}

void screen_loopView::btn_add_pressed(){
	state = ADD_FX;
}

void screen_loopView::btn_slot1_pressed()
{
	cont_Slot1.invalidate();
	switch (state)
	{
	case NORMAL:
		
		application().gotoscreen_fx_paramsScreenNoTransition();
		break;
	case ADD_FX:
		cont_Slot1.setVisible(true);
		break;
	case DELETE_FX:
		cont_Slot1.setVisible(false);
		break;
	default:
		break;
	}
	state = NORMAL;
	cont_Slot1.invalidate();
}

void screen_loopView::btn_slot2_pressed()
{
	cont_Slot2.invalidate();
	switch (state)
	{
	case NORMAL:
		application().gotoscreen_fx_paramsScreenNoTransition();
		break;
	case ADD_FX:
		cont_Slot2.setVisible(true);
		break;
	case DELETE_FX:
		cont_Slot2.setVisible(false);
		break;
	default:
		break;
	}
	state = NORMAL;
	cont_Slot2.invalidate();
}

void screen_loopView::btn_slot3_pressed()
{
	cont_Slot3.invalidate();
	switch (state)
	{
	case NORMAL:
		application().gotoscreen_fx_paramsScreenNoTransition();
		break;
	case ADD_FX:
		cont_Slot3.setVisible(true);
		break;
	case DELETE_FX:
		cont_Slot3.setVisible(false);	
		break;
	default:
		break;
	}
	state = NORMAL;
	cont_Slot3.invalidate();
}
