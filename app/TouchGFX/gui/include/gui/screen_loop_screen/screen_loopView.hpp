#ifndef SCREEN_LOOPVIEW_HPP
#define SCREEN_LOOPVIEW_HPP

#include <gui_generated/screen_loop_screen/screen_loopViewBase.hpp>
#include <gui/screen_loop_screen/screen_loopPresenter.hpp>

class screen_loopView : public screen_loopViewBase
{
public:
    screen_loopView();
    virtual ~screen_loopView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_LOOPVIEW_HPP