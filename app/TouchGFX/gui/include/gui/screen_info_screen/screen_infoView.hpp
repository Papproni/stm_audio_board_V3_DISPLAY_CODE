#ifndef SCREEN_INFOVIEW_HPP
#define SCREEN_INFOVIEW_HPP

#include <gui_generated/screen_info_screen/screen_infoViewBase.hpp>
#include <gui/screen_info_screen/screen_infoPresenter.hpp>

class screen_infoView : public screen_infoViewBase
{
public:
    screen_infoView();
    virtual ~screen_infoView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void updatescreen();

    virtual void btn_DSP_fw_update_pressed();
protected:
};

#endif // SCREEN_INFOVIEW_HPP
