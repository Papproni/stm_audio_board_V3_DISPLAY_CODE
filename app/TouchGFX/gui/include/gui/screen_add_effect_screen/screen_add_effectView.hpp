#ifndef SCREEN_ADD_EFFECTVIEW_HPP
#define SCREEN_ADD_EFFECTVIEW_HPP

#include <gui_generated/screen_add_effect_screen/screen_add_effectViewBase.hpp>
#include <gui/screen_add_effect_screen/screen_add_effectPresenter.hpp>
#include <touchgfx/Color.hpp>

#ifndef SIMULATOR

#endif

class screen_add_effectView : public screen_add_effectViewBase
{
public:
    screen_add_effectView();
    virtual ~screen_add_effectView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void update_screen();
    
    uint16_t choosen_fx_idx;
    uint8_t num_of_implemented_fx;
#ifndef SIMULATOR
    fx_data_tst* implemented_fx_ptr;
#endif

    void onItemSnap(int16_t itemIndex);
    virtual void btn_add_pressed();
    virtual void scrollList_FXUpdateItem(template_choose_fx& item, int16_t itemIndex);
protected:
private:
    touchgfx::Callback<screen_add_effectView, int16_t> itemSnapCallback;
};

#endif // SCREEN_ADD_EFFECTVIEW_HPP
