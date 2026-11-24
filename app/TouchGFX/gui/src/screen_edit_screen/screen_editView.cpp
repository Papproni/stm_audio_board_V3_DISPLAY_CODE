#include <gui/screen_edit_screen/screen_editView.hpp>


// Alpha values for elements
#define PATH_OFF 70
#define PATH_ON 255

#define PATH_EXTERNAL true
#define PATH_INTERNAL false

screen_editView::screen_editView() : boxClickedCallback(this ,&screen_editView::boxClickHandler)
{
	// In constructor for callback, bind to this view object and bind which function to handle the event.

}

void screen_editView::setupScreen()
{
    screen_editViewBase::setupScreen();
    // Horizontal scroll is owned by pot 0 (set_scroll_from_pot), not the finger:
    // a non-touchable container receives no click/drag/swipe events, so it can no
    // longer be scrolled by touch. Child widgets (buttons, signal lines) keep their
    // own touchability and stay clickable.
    scrollableContainer.setTouchable(false);

    // ---- Enlarge the touch footprint of the loop-toggle signal lines ----
    // Touch routing hit-tests on the widget bounding box (Container::getLastChild
    // uses getRect().intersect), while Line rendering is clipped to the line's
    // minimal rect - so widening the box ONLY makes the line easier to press
    // with a finger; the drawn line stays exactly where it was (endpoints are
    // shifted by the same amount as the widget origin).
    // Horizontal bypass lines: 110x15 -> 126x39 (L34: 126x36, bottom capped at
    // y=153 where the btn_Loop* row starts) - much taller tap band.
    line_signal_loop1_loop2_bypass.setPosition(70 - 8, 126 - 12, 110 + 16, 15 + 24);
    line_signal_loop1_loop2_bypass.setStart(10 + 8, 10 + 12);
    line_signal_loop1_loop2_bypass.setEnd(100 + 8, 10 + 12);

    line_signal_loop2_loop3_bypass.setPosition(200 - 8, 126 - 12, 110 + 16, 15 + 24);
    line_signal_loop2_loop3_bypass.setStart(10 + 8, 10 + 12);
    line_signal_loop2_loop3_bypass.setEnd(100 + 8, 10 + 12);

    line_signal_loop3_loop4_bypass.setPosition(330 - 8, 128 - 11, 110 + 16, 15 + 22);
    line_signal_loop3_loop4_bypass.setStart(10 + 8, 10 + 11);
    line_signal_loop3_loop4_bypass.setEnd(100 + 8, 10 + 11);

    // Vertical external lines: 21x67 -> 37x67 (wider tap column)
    line_signal_loop1_out_ext.setPosition(70 - 8, 86, 21 + 16, 67);
    line_signal_loop1_out_ext.setStart(10 + 8, 0);
    line_signal_loop1_out_ext.setEnd(10 + 8, 110);

    line_signal_loop2_in_ext.setPosition(160 - 8, 86, 21 + 16, 67);
    line_signal_loop2_in_ext.setStart(10 + 8, 0);
    line_signal_loop2_in_ext.setEnd(10 + 8, 110);

    line_signal_loop2_out_ext.setPosition(200 - 8, 86, 21 + 16, 67);
    line_signal_loop2_out_ext.setStart(10 + 8, 0);
    line_signal_loop2_out_ext.setEnd(10 + 8, 110);

    line_signal_loop3_in_ext.setPosition(290 - 8, 86, 21 + 16, 67);
    line_signal_loop3_in_ext.setStart(10 + 8, 0);
    line_signal_loop3_in_ext.setEnd(10 + 8, 110);

    line_signal_loop3_out_ext.setPosition(330 - 8, 86, 21 + 16, 67);
    line_signal_loop3_out_ext.setStart(10 + 8, 0);
    line_signal_loop3_out_ext.setEnd(10 + 8, 110);

    line_signal_loop4_in_ext.setPosition(420 - 8, 86, 21 + 16, 67);
    line_signal_loop4_in_ext.setStart(10 + 8, 0);
    line_signal_loop4_in_ext.setEnd(10 + 8, 110);

    line_signal_loop1_loop2_bypass.setClickAction(boxClickedCallback);
    line_signal_loop2_loop3_bypass.setClickAction(boxClickedCallback);
    line_signal_loop3_loop4_bypass.setClickAction(boxClickedCallback);

    line_signal_loop1_out_ext.setClickAction(boxClickedCallback);
    line_signal_loop2_in_ext.setClickAction(boxClickedCallback);

    line_signal_loop2_out_ext.setClickAction(boxClickedCallback);
    line_signal_loop3_in_ext.setClickAction(boxClickedCallback);

    line_signal_loop3_out_ext.setClickAction(boxClickedCallback);
	line_signal_loop4_in_ext.setClickAction(boxClickedCallback);
}

void screen_editView::tearDownScreen()
{
    screen_editViewBase::tearDownScreen();
}

void screen_editView::set_scroll_from_pot(uint32_t pot)
{
    if (pot > 65535u)
    {
        pot = 65535u;
    }
    // How far the content can be scrolled to the right: content width beyond the container window.
    // getContainedArea() = children union expanded over the window, so its width is the
    // content width (independent of the current scroll offset).
    const Rect contained = scrollableContainer.getContainedArea();
    int32_t maxRight = (int32_t)contained.width - (int32_t)scrollableContainer.getWidth();
    if (maxRight <= 0)
    {
        return; // content fits in the window - nothing to scroll
    }
    // pot = 65535 (full CW) -> targetX = 0 (left); pot = 0 (full CCW) -> targetX = -maxRight (right end)
    // round(maxRight * (65535 - pot) / 65535) in integer math: (a + b/2)/b with a = maxRight*(65535-pot), b = 65535
    int16_t targetX = -(int16_t)(((uint32_t)maxRight * (65535u - pot) + 32767u) / 65535u);
    int16_t delta = (int16_t)(targetX - contained.x);
    if (delta != 0)
    {
        // doScroll clamps to the left/right limits internally
        scrollableContainer.doScroll(delta, 0);
    }
}

void screen_editView::btn_loop1_pressed(){
#ifndef SIMULATOR
	// presenter->read_loopdata(LOOP1);
	presenter->set_current_loop_num(LOOP1);
#endif // !SIMULATOR
	application().gotoscreen_loopScreenNoTransition();
}
void screen_editView::btn_loop2_pressed(){
#ifndef SIMULATOR
	// presenter->read_loopdata(LOOP2);
	presenter->set_current_loop_num(LOOP2);
#endif
	application().gotoscreen_loopScreenNoTransition();
}
void screen_editView::btn_loop3_pressed(){
#ifndef SIMULATOR
	// presenter->read_loopdata(LOOP3);
	presenter->set_current_loop_num(LOOP3);
#endif // !SIMULATOR
	application().gotoscreen_loopScreenNoTransition();
}
void screen_editView::btn_loop4_pressed(){
#ifndef SIMULATOR
	// presenter->read_loopdata(LOOP4);
	presenter->set_current_loop_num(LOOP4);
#endif // !SIMULATOR
	application().gotoscreen_loopScreenNoTransition();
}

void screen_editView::setAlphaOfContainer(Container &conti,uint8_t alpha){
	auto* d = conti.getFirstChild();
	while(d!=NULL){
		touchgfx::Line* line = (touchgfx::Line*)(d);
		line->setAlpha(alpha);
		line->invalidate(); // Redraw to apply the new alpha
		d = d->getNextSibling();
	}
}
volatile bool L12_ext = true;
volatile bool L23_ext = true;
volatile bool L34_ext = true;

void screen_editView::update_screen()
{
	
// Current preset number in the top-right container (same values as screen_perf_mode)
#ifndef SIMULATOR
	mode_preset_display_container1.set_current_preset(preset_data_un.preset_Major_u8, preset_data_un.preset_Minor_u8);
	mode_preset_display_container1.set_active_mode(preset_data_un.fx_active_mode_u8);
#else
	mode_preset_display_container1.set_current_preset('Z', 9);
	mode_preset_display_container1.set_active_mode(0);
#endif

#ifndef SIMULATOR
	L12_ext = this->loopbypass.L12;
	L23_ext = this->loopbypass.L23;
	L34_ext = this->loopbypass.L34;
#endif	
	
	scrollableContainer.invalidate();
	if (L12_ext){
		setAlphaOfContainer(container_loop1_loop2_ext, PATH_ON);
		setAlphaOfContainer(container_loop1_loop2_internal_bypass, PATH_OFF);
	}else{
		setAlphaOfContainer(container_loop1_loop2_ext, PATH_OFF);
		setAlphaOfContainer(container_loop1_loop2_internal_bypass, PATH_ON);
	}

	if (L23_ext){
		setAlphaOfContainer(container_loop2_loop3_ext, PATH_ON);
		setAlphaOfContainer(container_loop2_loop3_internal_bypass, PATH_OFF);
	}else{
		setAlphaOfContainer(container_loop2_loop3_ext, PATH_OFF);
		setAlphaOfContainer(container_loop2_loop3_internal_bypass, PATH_ON);
	}
	if (L34_ext){
		setAlphaOfContainer(container_loop3_loop4_ext, PATH_ON);
		setAlphaOfContainer(container_loop3_loop4_internal_bypass, PATH_OFF);
	}else{
		setAlphaOfContainer(container_loop3_loop4_ext, PATH_OFF);
		setAlphaOfContainer(container_loop3_loop4_internal_bypass, PATH_ON);
	}

}


void screen_editView::boxClickHandler(const Line & b, const ClickEvent& evt)
{
    if (&b == &line_signal_loop1_loop2_bypass || &b == &line_signal_loop1_out_ext || &b == &line_signal_loop2_in_ext )
    {
    	if(evt.getType() == ClickEvent::RELEASED){
    		L12_ext = !L12_ext;
			presenter->set_loopbypass(L12_LOC,L12_ext);
    	}
    }
    if (&b == &line_signal_loop2_loop3_bypass || &b == &line_signal_loop2_out_ext || &b == &line_signal_loop3_in_ext)
	{
    	if(evt.getType() == ClickEvent::RELEASED){
    		L23_ext = !L23_ext;
			presenter->set_loopbypass(L23_LOC,L23_ext);
    	}
	}
    if (&b == &line_signal_loop3_loop4_bypass || &b == &line_signal_loop3_out_ext || &b == &line_signal_loop4_in_ext)
	{
    	if(evt.getType() == ClickEvent::RELEASED){
    		L34_ext = !L34_ext;
			presenter->set_loopbypass(L34_LOC,L34_ext);
		}
	}
}
