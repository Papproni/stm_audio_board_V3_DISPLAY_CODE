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
    DELETE_FX,
    MOVE_FX
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
    virtual void toggleBtn_slot1_pressed();
    virtual void toggleBtn_slot2_pressed();
    virtual void toggleBtn_slot3_pressed();
    virtual void btn_del_pressed();
    virtual void btn_add_pressed();
    virtual void btn_move_pressed();


    virtual void update_screen();

    screen_states_ten state;
    int move_source_slot; // 1..3 slot selected as source in MOVE_FX mode, 0 = none yet
    void refresh_move_glow();

    // MOVE button - owned by this view (not in generated base) so Designer regeneration can't wipe it
    touchgfx::ButtonWithLabel btn_Move_fx;
    touchgfx::Callback<screen_loopView, const touchgfx::AbstractButton&> moveBtnCallback;
    void moveBtnCallbackHandler(const touchgfx::AbstractButton& src);

#ifndef SIMULATOR
    sab_loop_num_tun loop_num_un;
    sab_preset_num_tun preset_data_un;
    bool slot_has_fx(int slot);
    fx_data_tst* slot_ptr(int slot);
#else
    inline bool slot_has_fx(int) { return true; }
#endif
    int inited;
//    virtual char* get_current_fx_name();
protected:
    
    
};

#endif // SCREEN_LOOPVIEW_HPP
