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

void setAlphaOfContainer(Container &conti,uint8_t alpha){
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
	scrollableContainer.invalidate();
//	setAlphaForAllElements(container_loop1_loop2_ext,				PATH_OFF);
//	setAlphaForAllElements(container_loop1_loop2_internal_bypass	,PATH_ON);
//	container_loop1_loop2_ext.forEachChild(setAlpha(container_loop1_loop2_ext, PATH_ON));
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
    	if(evt.getType() == ClickEvent::PRESSED){
    		L12_ext = !L12_ext;
    	}
    }
    if (&b == &line_signal_loop2_loop3_bypass || &b == &line_signal_loop2_out_ext || &b == &line_signal_loop3_in_ext)
	{
    	if(evt.getType() == ClickEvent::PRESSED){
    		L23_ext = !L23_ext;
    	}
	}
    if (&b == &line_signal_loop3_loop4_bypass || &b == &line_signal_loop3_out_ext || &b == &line_signal_loop4_in_ext)
	{
    	if(evt.getType() == ClickEvent::PRESSED){
    		L34_ext = !L34_ext;
		}
	}

//
//    if (&b == &line_signal_loop1_out_ext || &b == &line_signal_loop2_in_ext )
//	{
//		L12_ext = PATH_EXTERNAL;
//	}
//	if (&b == &line_signal_loop2_out_ext || &b == &line_signal_loop3_in_ext)
//	{
//		L23_ext = PATH_EXTERNAL;
//	}
//	if (&b == &line_signal_loop3_out_ext || &b == &line_signal_loop4_in_ext)
//	{
//		L34_ext = PATH_EXTERNAL;
//	}
}
