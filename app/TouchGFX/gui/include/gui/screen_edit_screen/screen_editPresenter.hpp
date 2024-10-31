#ifndef SCREEN_EDITPRESENTER_HPP
#define SCREEN_EDITPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_editView;

class screen_editPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_editPresenter(screen_editView& v);

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
    virtual void update_screen();

#ifndef SIMULATOR
    void set_current_loop_num(uint8_t loopnum);
    void set_current_fx_slot_num(uint8_t slotnum);

    // virtual uint8_t get_current_loop_num();
    // virtual uint8_t get_current_fx_slot_num();
#endif // !SIMULATOR


    void read_loopdata(uint8_t loopnum);
    void set_loopbypass(uint8_t loop, uint8_t state);
    virtual ~screen_editPresenter() {}

private:
    screen_editPresenter();

    screen_editView& view;
};

#endif // SCREEN_EDITPRESENTER_HPP
