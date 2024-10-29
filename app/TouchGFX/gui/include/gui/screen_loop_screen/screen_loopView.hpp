#ifndef SCREEN_LOOPVIEW_HPP
#define SCREEN_LOOPVIEW_HPP

#include <gui_generated/screen_loop_screen/screen_loopViewBase.hpp>
#include <gui/screen_loop_screen/screen_loopPresenter.hpp>
#include <touchgfx/Color.hpp>

#ifndef SIMULATOR
#include "sab_intercom.h"
#endif

typedef enum screen_states_en{
    NORMAL,
    ADD_FX,
    DELETE_FX
}screen_states_ten;

class screen_loopView : public screen_loopViewBase
{
public:
    screen_loopView();
    virtual ~screen_loopView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void btn_slot1_pressed();
    virtual void btn_slot2_pressed();
    virtual void btn_slot3_pressed();
    virtual void btn_del_pressed();
    virtual void btn_add_pressed();

    virtual void update_screen();

    screen_states_ten state;

#ifndef SIMULATOR
    sab_loop_num_tun loop_num_un;
#endif
#ifdef SIMULATOR
    int inited;
#endif // DEBUG
//    virtual char* get_current_fx_name();
protected:
    
    
};

#endif // SCREEN_LOOPVIEW_HPP
