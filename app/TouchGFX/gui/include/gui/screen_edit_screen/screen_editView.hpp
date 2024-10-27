#ifndef SCREEN_EDITVIEW_HPP
#define SCREEN_EDITVIEW_HPP

#include <gui_generated/screen_edit_screen/screen_editViewBase.hpp>
#include <gui/screen_edit_screen/screen_editPresenter.hpp>
#ifndef SIMULATOR
#include "sab_intercom.h"
#endif

enum loop_pos{
    L12_LOC,
    L23_LOC,
    L34_LOC
};

enum loop_nums{
    LOOP1 = 1,
    LOOP2,
    LOOP3,
    LOOP4
};
class screen_editView : public screen_editViewBase
{
public:
    screen_editView();
    virtual ~screen_editView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void update_screen();

    virtual void btn_loop1_pressed();
    virtual void btn_loop2_pressed();
    virtual void btn_loop3_pressed();
    virtual void btn_loop4_pressed();
    // Declaring callback handler for Box
    void boxClickHandler(const Line& b, const ClickEvent& e);
    void setAlphaOfContainer(Container &conti,uint8_t alpha);
#ifndef SIMULATOR
    sab_loopbypass_tun loopbypass;
#endif

protected:
    // Declaring callback type of box and clickEvent
    Callback<screen_editView, const Line&, const ClickEvent&> boxClickedCallback;
};

#endif // SCREEN_EDITVIEW_HPP
