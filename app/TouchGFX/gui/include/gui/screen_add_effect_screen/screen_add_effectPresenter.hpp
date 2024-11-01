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

    virtual void deactivate();
    virtual void update_screen();


    virtual ~screen_add_effectPresenter() {}

private:
    screen_add_effectPresenter();

    screen_add_effectView& view;
};

#endif // SCREEN_ADD_EFFECTPRESENTER_HPP
