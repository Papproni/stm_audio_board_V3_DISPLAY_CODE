#include <gui/screen_add_effect_screen/screen_add_effectView.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include "string.h"
#ifdef SIMULATOR
#include <touchgfx/Utils.hpp>
#endif

screen_add_effectView::screen_add_effectView() : itemSnapCallback(this, &screen_add_effectView::onItemSnap)
{
}

void screen_add_effectView::setupScreen()
{
    screen_add_effectViewBase::setupScreen();

    scrollList_FX.setItemSelectedCallback(itemSnapCallback);
}

void screen_add_effectView::tearDownScreen()
{
    screen_add_effectViewBase::tearDownScreen();
}

void screen_add_effectView::onItemSnap(int16_t itemIndex) {
#ifdef SIMULATOR
    touchgfx_printf("Snapped item index: %d\n", itemIndex);
#endif
    choosen_fx_idx = itemIndex;
    presenter->add_effect(choosen_fx_idx);
#ifndef SIMULATOR
    application().gotoscreen_loopScreenNoTransition();
#endif
}

volatile uint8_t red;
void screen_add_effectView::scrollList_FXUpdateItem(template_choose_fx &item, int16_t itemIndex)
{
    //    item.textArea.invalidate();
    Drawable *myptr = item.getFirstChild();
    touchgfx::Box *box = (touchgfx::Box *)(myptr);

#ifndef SIMULATOR

    if(this->implemented_fx_ptr == NULL){
    	return;
    }
    touchgfx::Unicode::UnicodeChar* buff_ptr = item.get_buffer();
    Unicode::strncpy(buff_ptr, this->implemented_fx_ptr[itemIndex].name, 10);
    uint8_t r = this->implemented_fx_ptr[itemIndex].color[0];
    uint8_t g = this->implemented_fx_ptr[itemIndex].color[1];
    uint8_t b = this->implemented_fx_ptr[itemIndex].color[2];
    box->setColor(touchgfx::Color::getColorFromRGB(r, g, b));
#endif

#ifdef SIMULATOR
    touchgfx_printf("updated_item: %d\n", itemIndex);
    red = itemIndex * 25;
    if (0 == itemIndex)
    {
        Unicode::strncpy(item.get_buffer(), "Octave", 10);
        box->setColor(touchgfx::Color::getColorFromRGB(255, 20, 50));
    }

    else if (1 == itemIndex)
    {
        Unicode::strncpy(item.get_buffer(), "Delay", 10);
        box->setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));
    }
    else if (2 == itemIndex)
    {
        Unicode::strncpy(item.get_buffer(), "Reverb", 10);
        box->setColor(touchgfx::Color::getColorFromRGB(0, 255, 255));
    }
    else if (3 == itemIndex)
    {
        Unicode::strncpy(item.get_buffer(), "Overdrive", 10);
        box->setColor(touchgfx::Color::getColorFromRGB(100, 255, 100));
    }
#endif

    item.get_text_wc().resizeToCurrentText();
    item.get_text_wc().invalidate();
    box->invalidate();
}

void screen_add_effectView::btn_add_pressed(){

}

void screen_add_effectView::update_screen()
{
#ifndef SIMULATOR
    scrollList_FX.setNumberOfItems(this->num_of_implemented_fx);
#endif
#ifdef SIMULATOR
    scrollList_FX.setNumberOfItems(4);
    
#endif
    scrollList_FX.invalidate();
}
