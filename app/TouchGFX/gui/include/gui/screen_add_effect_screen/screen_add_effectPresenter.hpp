#ifndef SCREEN_ADD_EFFECTPRESENTER_HPP
#define SCREEN_ADD_EFFECTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_add_effectView;

class screen_add_effectPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_add_effectPresenter(screen_add_effectView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
#ifndef SIMULATOR
    sab_loop_num_tun loop_data;
#endif
    void add_effect(uint8_t choosen_fx);
    void add_current_effect();   // commit the effect currently centered by the pot scroll

    virtual void deactivate();
    virtual void update_screen();


    virtual ~screen_add_effectPresenter() {}

private:
    screen_add_effectPresenter();

    screen_add_effectView& view;
    uint8_t last_preset_major_u8; // 0xFF = not read yet (sentinel); preset-change detection
    uint8_t last_preset_minor_u8;
    int16_t scroll_index;         // effect currently centered in the list (driven by pot 0)
    int16_t num_effects;          // number of selectable effects this screen shows
};

#endif // SCREEN_ADD_EFFECTPRESENTER_HPP
