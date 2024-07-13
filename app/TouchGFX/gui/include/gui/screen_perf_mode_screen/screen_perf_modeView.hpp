#ifndef SCREEN_PERF_MODEVIEW_HPP
#define SCREEN_PERF_MODEVIEW_HPP

#include <gui_generated/screen_perf_mode_screen/screen_perf_modeViewBase.hpp>
#include <gui/screen_perf_mode_screen/screen_perf_modePresenter.hpp>

class screen_perf_modeView : public screen_perf_modeViewBase
{
public:
    screen_perf_modeView();
    virtual ~screen_perf_modeView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_PERF_MODEVIEW_HPP
