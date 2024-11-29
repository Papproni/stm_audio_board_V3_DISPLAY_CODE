#include <gui/screen_loop_screen/screen_loopView.hpp>

screen_loopView::screen_loopView()
{
	state = NORMAL;
	inited = 0;
}

void screen_loopView::setupScreen()
{
    screen_loopViewBase::setupScreen();
}

void screen_loopView::tearDownScreen()
{
    screen_loopViewBase::tearDownScreen();
}


void screen_loopView::toggleBtn_slot1_pressed(){
	loop_num_un.slot1.fx_state_en = (this->toggleBtn_slot1.getState() == 0) ? FX_STATE_OFF : FX_STATE_ON;
	presenter->set_loop_data();
}
void screen_loopView::toggleBtn_slot2_pressed(){
	loop_num_un.slot2.fx_state_en = (this->toggleBtn_slot2.getState() == 0) ? FX_STATE_OFF : FX_STATE_ON;
	presenter->set_loop_data();
}
void screen_loopView::toggleBtn_slot3_pressed(){
	loop_num_un.slot3.fx_state_en = (this->toggleBtn_slot3.getState() == 0) ? FX_STATE_OFF : FX_STATE_ON;
	presenter->set_loop_data();
}
// #define SIMULATOR

void screen_loopView::update_screen()
{
#ifndef SIMULATOR
	if(0 == inited){
		this->toggleBtn_slot1.forceState(loop_num_un.slot1.fx_state_en == FX_STATE_ON);
		this->toggleBtn_slot2.forceState(loop_num_un.slot2.fx_state_en == FX_STATE_ON);
		this->toggleBtn_slot3.forceState(loop_num_un.slot3.fx_state_en == FX_STATE_ON);
		inited = 1;
	}

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
		Unicode::strncpy(text_FXname_2Buffer,loop_num_un.slot2.name,10);
		box_FX_background_2.setColor(touchgfx::Color::getColorFromRGB(loop_num_un.slot2.color[0], loop_num_un.slot2.color[1], loop_num_un.slot2.color[2]));
		text_FXname_2.resizeToCurrentText();
		text_FXname_2.invalidate();

	}else{
		cont_Slot2.setVisible(false);
	}
	if(strcmp(loop_num_un.slot3.name,"NONE")){
		cont_Slot3.setVisible(true);
		Unicode::strncpy(text_FXname_3Buffer,loop_num_un.slot3.name,10);
		box_FX_background_3.setColor(touchgfx::Color::getColorFromRGB(loop_num_un.slot3.color[0], loop_num_un.slot3.color[1], loop_num_un.slot3.color[2]));
		text_FXname_3.resizeToCurrentText();
		text_FXname_3.invalidate();
	}else{
		cont_Slot3.setVisible(false);
	}

#endif // !SIMULATOR



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

#ifdef SIMULATOR
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
#ifndef SIMULATOR
		if(0 != strcmp(loop_num_un.slot1.name,"NONE")){
			presenter->add_fx(FX_SLOT1);
			application().gotoscreen_fx_paramsScreenNoTransition();
		}
#endif
		
		break;
	case ADD_FX:
		// cont_Slot1.setVisible(true);
#ifndef SIMULATOR
		presenter->add_fx(FX_SLOT1);
#endif
		application().gotoscreen_add_effectScreenNoTransition();
		break;
	case DELETE_FX:
		cont_Slot1.setVisible(false);
		#ifndef SIMULATOR
		strcpy(loop_num_un.slot1.name,"NONE");
		presenter->set_loop_data();
		#endif
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
#ifndef SIMULATOR
		if(0 != strcmp(loop_num_un.slot2.name,"NONE")){
			presenter->add_fx(FX_SLOT2);
			application().gotoscreen_fx_paramsScreenNoTransition();
		}
#endif
		break;
	case ADD_FX:
		// cont_Slot2.setVisible(true);
#ifndef SIMULATOR
		presenter->add_fx(FX_SLOT2);
#endif
		application().gotoscreen_add_effectScreenNoTransition();
		break;
	case DELETE_FX:
		cont_Slot2.setVisible(false);
#ifndef SIMULATOR
		strcpy(loop_num_un.slot2.name,"NONE");
		presenter->set_loop_data();
#endif
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
#ifndef SIMULATOR
		if(0 != strcmp(loop_num_un.slot3.name,"NONE")){
			presenter->add_fx(FX_SLOT3);
			application().gotoscreen_fx_paramsScreenNoTransition();
		}
#endif
		break;
	case ADD_FX:
		// cont_Slot3.setVisible(true);
#ifndef SIMULATOR
		presenter->add_fx(FX_SLOT3);
#endif	
		application().gotoscreen_add_effectScreenNoTransition();
		break;
	case DELETE_FX:
		cont_Slot3.setVisible(false);	
#ifndef SIMULATOR
		strcpy(loop_num_un.slot3.name,"NONE");
		presenter->set_loop_data();
#endif
		break;
	default:
		break;
	}
	state = NORMAL;
	cont_Slot3.invalidate();
}
