#include <gui/screen_loop_screen/screen_loopView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>

screen_loopView::screen_loopView()
{
	state = NORMAL;
	move_source_slot = 0;
	inited = 0;
}

void screen_loopView::setupScreen()
{
    screen_loopViewBase::setupScreen();

    // MOVE button: built by this view (positioned in the gap between btn_opt and btn_Add_fx)
    btn_Move_fx.setXY(65, 0);
    btn_Move_fx.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_FILL_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_FILL_DISABLED_ID));
    btn_Move_fx.setLabelText(touchgfx::TypedText(T___SINGLEUSE_MVFX));
    btn_Move_fx.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    btn_Move_fx.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    moveBtnCallback = touchgfx::Callback<screen_loopView, const touchgfx::AbstractButton&>(this, &screen_loopView::moveBtnCallbackHandler);
    btn_Move_fx.setAction(moveBtnCallback);
    add(btn_Move_fx);
}

void screen_loopView::moveBtnCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &btn_Move_fx)
    {
        btn_move_pressed();
    }
}

void screen_loopView::tearDownScreen()
{
    screen_loopViewBase::tearDownScreen();
}


void screen_loopView::toggleBtn_slot1_pressed(){
	#ifndef SIMULATOR
	loop_num_un.slot1.fx_state_en = (this->toggleBtn_slot1.getState() == 0) ? FX_STATE_OFF : FX_STATE_ON;
	presenter->set_loop_data();
	#endif
}
void screen_loopView::toggleBtn_slot2_pressed(){
	#ifndef SIMULATOR
	loop_num_un.slot2.fx_state_en = (this->toggleBtn_slot2.getState() == 0) ? FX_STATE_OFF : FX_STATE_ON;
	presenter->set_loop_data();
	#endif
}
void screen_loopView::toggleBtn_slot3_pressed(){
	#ifndef SIMULATOR
	loop_num_un.slot3.fx_state_en = (this->toggleBtn_slot3.getState() == 0) ? FX_STATE_OFF : FX_STATE_ON;
	presenter->set_loop_data();
	#endif
}
// #define SIMULATOR

// MOVE helpers --------------------------------------------------------------
#ifndef SIMULATOR
bool screen_loopView::slot_has_fx(int slot)
{
	switch (slot)
	{
	case 1: return strcmp(loop_num_un.slot1.name, "NONE") != 0;
	case 2: return strcmp(loop_num_un.slot2.name, "NONE") != 0;
	case 3: return strcmp(loop_num_un.slot3.name, "NONE") != 0;
	}
	return false;
}

fx_data_tst* screen_loopView::slot_ptr(int slot)
{
	switch (slot)
	{
	case 1: return &loop_num_un.slot1;
	case 2: return &loop_num_un.slot2;
	default: return &loop_num_un.slot3;
	}
}
#endif

void screen_loopView::refresh_move_glow()
{
	if (state == MOVE_FX)
	{
		glow_1.setVisible(slot_has_fx(1));
		glow_2.setVisible(slot_has_fx(2));
		glow_3.setVisible(slot_has_fx(3));

		touchgfx::colortype src_color = touchgfx::Color::getColorFromRGB(255, 255, 0); // yellow = selected source (border ring; fill is hidden behind FX box)
		if (move_source_slot == 1) glow_1.setBorderColor(src_color);
		if (move_source_slot == 2) glow_2.setBorderColor(src_color);
		if (move_source_slot == 3) glow_3.setBorderColor(src_color);
	}
	else
	{
		touchgfx::colortype def_color = touchgfx::Color::getColorFromRGB(161, 58, 58); // reset to default so re-entering MOVE starts clean
		touchgfx::colortype def_border = touchgfx::Color::getColorFromRGB(255, 255, 255);
		glow_1.setColor(def_color);
		glow_2.setColor(def_color);
		glow_3.setColor(def_color);
		glow_1.setBorderColor(def_border);
		glow_2.setBorderColor(def_border);
		glow_3.setBorderColor(def_border);
		glow_1.setVisible(false);
		glow_2.setVisible(false);
		glow_3.setVisible(false);
	}

	glow_1.invalidate();
	glow_2.invalidate();
	glow_3.invalidate();
}

void screen_loopView::update_screen()
{
// Current preset number in the top-right container (same values as screen_perf_mode)
#ifndef SIMULATOR
	mode_preset_display_container1.set_current_preset(preset_data_un.preset_Major_u8, preset_data_un.preset_Minor_u8);
#else
	mode_preset_display_container1.set_current_preset('Z', 9);
#endif

#ifndef SIMULATOR
	this->toggleBtn_slot1.forceState(loop_num_un.slot1.fx_state_en == FX_STATE_ON);
	this->toggleBtn_slot2.forceState(loop_num_un.slot2.fx_state_en == FX_STATE_ON);
	this->toggleBtn_slot3.forceState(loop_num_un.slot3.fx_state_en == FX_STATE_ON);
	toggleBtn_slot1.invalidate();
	toggleBtn_slot2.invalidate();
	toggleBtn_slot3.invalidate();

	if(strcmp(loop_num_un.slot1.name,"NONE")){
		cont_Slot1.setVisible(true);
		Unicode::strncpy(text_FXname_1Buffer,loop_num_un.slot1.name,10);
		box_FX_background_1.setColor(touchgfx::Color::getColorFromRGB(loop_num_un.slot1.color[0], loop_num_un.slot1.color[1], loop_num_un.slot1.color[2]));
		text_FXname_1.resizeToCurrentText();
		text_FXname_1.invalidate();
		toggleBtn_slot1.setVisible(true);
	}else{
		cont_Slot1.setVisible(false);
		toggleBtn_slot1.setVisible(false);
	}

	if(strcmp(loop_num_un.slot2.name,"NONE")){
		cont_Slot2.setVisible(true);
		Unicode::strncpy(text_FXname_2Buffer,loop_num_un.slot2.name,10);
		box_FX_background_2.setColor(touchgfx::Color::getColorFromRGB(loop_num_un.slot2.color[0], loop_num_un.slot2.color[1], loop_num_un.slot2.color[2]));
		text_FXname_2.resizeToCurrentText();
		text_FXname_2.invalidate();
		toggleBtn_slot2.setVisible(true);
	}else{
		cont_Slot2.setVisible(false);
		toggleBtn_slot2.setVisible(false);
	}
	if(strcmp(loop_num_un.slot3.name,"NONE")){
		cont_Slot3.setVisible(true);
		Unicode::strncpy(text_FXname_3Buffer,loop_num_un.slot3.name,10);
		box_FX_background_3.setColor(touchgfx::Color::getColorFromRGB(loop_num_un.slot3.color[0], loop_num_un.slot3.color[1], loop_num_un.slot3.color[2]));
		text_FXname_3.resizeToCurrentText();
		text_FXname_3.invalidate();
		toggleBtn_slot3.setVisible(true);
	}else{
		cont_Slot3.setVisible(false);
		toggleBtn_slot3.setVisible(false);
	}
	cont_Slot1.invalidate();
	cont_Slot2.invalidate();
	cont_Slot3.invalidate();

#endif // !SIMULATOR



	switch (state)
	{
    case ADD_FX:
	case DELETE_FX:
		glow_1.setVisible(true);
		glow_2.setVisible(true);
		glow_3.setVisible(true);

		glow_1.invalidate();
		glow_2.invalidate();
		glow_3.invalidate();
		break;

	case MOVE_FX:
		refresh_move_glow();
		break;

	case NORMAL:
	{
		touchgfx::colortype def_color = touchgfx::Color::getColorFromRGB(161, 58, 58);
		touchgfx::colortype def_border = touchgfx::Color::getColorFromRGB(255, 255, 255);
		glow_1.setColor(def_color);
		glow_2.setColor(def_color);
		glow_3.setColor(def_color);
		glow_1.setBorderColor(def_border);
		glow_2.setBorderColor(def_border);
		glow_3.setBorderColor(def_border);

		glow_1.setVisible(false);
		glow_2.setVisible(false);
		glow_3.setVisible(false);

		glow_1.invalidate();
		glow_2.invalidate();
		glow_3.invalidate();
		break;
	}
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
	update_screen();
}

void screen_loopView::btn_add_pressed(){
	if(ADD_FX == state){
		state = NORMAL;
	}else{
		state = ADD_FX;
	}
	update_screen();
}

void screen_loopView::btn_move_pressed(){
	if(MOVE_FX == state){
		state = NORMAL;
		move_source_slot = 0;
	}else{
		state = MOVE_FX;
		move_source_slot = 0;
	}
	update_screen();
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
	case MOVE_FX:
		// first tap: mark this slot as the move source (only if it has an fx)
		if(move_source_slot == 0){
			if(slot_has_fx(1)){
				move_source_slot = 1;
			}
		}else if(move_source_slot != 1){
			// second tap: swap source fx into slot 1 (keeps any fx already there)
			#ifndef SIMULATOR
				// move the effect's parameters along with it (DSP keeps params per slot position on rebuild)
				presenter->swap_slot_fx_params(move_source_slot - 1, 0);
				fx_data_tst* src = slot_ptr(move_source_slot);
				fx_data_tst dst = loop_num_un.slot1;
				loop_num_un.slot1 = *src;
				*src = dst;
				presenter->set_loop_data();
			#endif
			state = NORMAL;
			move_source_slot = 0;
		}
		break;
	default:
		break;
	}
	if(state != MOVE_FX){
		state = NORMAL;
	}
	cont_Slot1.invalidate();
	update_screen();
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
	case MOVE_FX:
		if(move_source_slot == 0){
			if(slot_has_fx(2)){
				move_source_slot = 2;
			}
		}else if(move_source_slot != 2){
#ifndef SIMULATOR
			// move the effect's parameters along with it (DSP keeps params per slot position on rebuild)
			presenter->swap_slot_fx_params(move_source_slot - 1, 1);
			fx_data_tst* src = slot_ptr(move_source_slot);
			fx_data_tst dst = loop_num_un.slot2;
			loop_num_un.slot2 = *src;
			*src = dst;
			presenter->set_loop_data();
#endif
			state = NORMAL;
			move_source_slot = 0;
		}
		break;
	default:
		break;
	}
	if(state != MOVE_FX){
		state = NORMAL;
	}
	cont_Slot2.invalidate();
	update_screen();
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
	case MOVE_FX:
		if(move_source_slot == 0){
			if(slot_has_fx(3)){
				move_source_slot = 3;
			}
		}else if(move_source_slot != 3){
#ifndef SIMULATOR
			// move the effect's parameters along with it (DSP keeps params per slot position on rebuild)
			presenter->swap_slot_fx_params(move_source_slot - 1, 2);
			fx_data_tst* src = slot_ptr(move_source_slot);
			fx_data_tst dst = loop_num_un.slot3;
			loop_num_un.slot3 = *src;
			*src = dst;
			presenter->set_loop_data();
#endif
			state = NORMAL;
			move_source_slot = 0;
		}
		break;
	default:
		break;
	}
	if(state != MOVE_FX){
		state = NORMAL;
	}
	cont_Slot3.invalidate();
	update_screen();
}
