#ifndef SCREEN_TUNINGVIEW_HPP
#define SCREEN_TUNINGVIEW_HPP

#include <gui_generated/screen_tuning_screen/screen_tuningViewBase.hpp>
#include <gui/screen_tuning_screen/screen_tuningPresenter.hpp>

#ifndef SIMULATOR
#include "sab_intercom.h"
#endif

class screen_tuningView : public screen_tuningViewBase
{
public:
    screen_tuningView();
    virtual ~screen_tuningView() {}
    virtual void update_screen();

#ifndef SIMULATOR
    // Live tuner data pushed in by the presenter each frame.
    sab_tuner_data_tun tuner_un;
#endif

private:
    // Change-detection so the note labels / needle only repaint when they move.
    int8_t  last_pc_s8;          // last middle pitch class shown (-1 = none yet)
    int16_t last_needle_deg_s16; // last needle center angle in deg (1000 = not set)
};

#endif // SCREEN_TUNINGVIEW_HPP
