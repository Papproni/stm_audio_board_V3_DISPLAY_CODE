#ifndef SCREEN_TUNINGVIEW_HPP
#define SCREEN_TUNINGVIEW_HPP

#include <gui_generated/screen_tuning_screen/screen_tuningViewBase.hpp>
#include <gui/screen_tuning_screen/screen_tuningPresenter.hpp>

class screen_tuningView : public screen_tuningViewBase
{
public:
    screen_tuningView();
    virtual ~screen_tuningView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_TUNINGVIEW_HPP
