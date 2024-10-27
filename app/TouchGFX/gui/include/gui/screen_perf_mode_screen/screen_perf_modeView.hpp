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

    virtual void update_screen();
    #ifndef SIMULATOR
    sab_preset_num_tun preset_data_un;
    #endif
protected:
    
};

#endif // SCREEN_PERF_MODEVIEW_HPP
