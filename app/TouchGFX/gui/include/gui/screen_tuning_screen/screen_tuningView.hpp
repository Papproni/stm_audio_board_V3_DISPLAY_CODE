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
};

#endif // SCREEN_TUNINGVIEW_HPP
