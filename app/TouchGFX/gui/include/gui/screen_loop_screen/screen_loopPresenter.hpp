#ifndef SCREEN_LOOPPRESENTER_HPP
#define SCREEN_LOOPPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_loopView;

class screen_loopPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_loopPresenter(screen_loopView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

//    virtual char* get_current_fx_name();
    virtual ~screen_loopPresenter() {}

    void setFXname(char* name);
    virtual void update_screen();
    void set_loop_data();
#ifndef  SIMULATOR
    void add_fx(fx_slots_ten slot);
#endif

private:
    screen_loopPresenter();

    screen_loopView& view;
};

#endif // SCREEN_LOOPPRESENTER_HPP
