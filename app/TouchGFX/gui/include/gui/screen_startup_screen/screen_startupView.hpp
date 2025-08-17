#ifndef SCREEN_STARTUPVIEW_HPP
#define SCREEN_STARTUPVIEW_HPP

#include <gui_generated/screen_startup_screen/screen_startupViewBase.hpp>
#include <gui/screen_startup_screen/screen_startupPresenter.hpp>

class screen_startupView : public screen_startupViewBase
{
public:
    screen_startupView();
    virtual ~screen_startupView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_STARTUPVIEW_HPP
