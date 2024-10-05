#include <gui/screen_edit_screen/screen_editView.hpp>


// Alpha values for elements
#define PATH_OFF 70
#define PATH_ON 255

screen_editView::screen_editView()
{

}

void screen_editView::setupScreen()
{
    screen_editViewBase::setupScreen();
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
