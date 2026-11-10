#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>

class FrontendHeap;

using namespace touchgfx;

/**
 * Application controller.
 *
 * On top of the generated base it adds one behaviour: automatic navigation driven by the
 * DSP tuner state. When the DSP engages the tuner (sab_tuner_data_tun.active_u8 == 1) the UI
 * jumps to the tuning screen; when the DSP disengages it returns to the screen that was
 * showing before. The active screen is tracked by shadowing every generated gotoscreen_*()
 * method: all navigation in this project reaches those methods through application(), which
 * returns FrontendApplication& (the concrete type), so name-hiding routes each transition
 * through the overrides below and keeps currentScreenId accurate with no edits to the views.
 */
class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    // Logical screen identifiers, one per TouchGFX screen.
    enum ScreenId
    {
        SCR_STARTUP = 0,
        SCR_SETTINGS,
        SCR_TUNING,
        SCR_PERF_MODE,
        SCR_INFO,
        SCR_FX_PARAMS,
        SCR_CONFIG,
        SCR_LOOP,
        SCR_EDIT,
        SCR_ADD_EFFECT,
        NUM_SCREENS
    };

    virtual void handleTickEvent();

    // Shadows of the generated navigation methods: record the active screen, then perform
    // the real transition. Keep in sync with FrontendApplicationBase's gotoscreen_*.
    void gotoscreen_startupScreenNoTransition();
    void gotoscreen_settingsScreenNoTransition();
    void gotoscreen_tuningScreenNoTransition();
    void gotoscreen_perf_modeScreenNoTransition();
    void gotoscreen_perf_modeScreenCoverTransitionEast();
    void gotoscreen_infoScreenNoTransition();
    void gotoscreen_fx_paramsScreenNoTransition();
    void gotoscreen_configScreenNoTransition();
    void gotoscreen_loopScreenNoTransition();
    void gotoscreen_editScreenNoTransition();
    void gotoscreen_add_effectScreenNoTransition();

private:
    void pollTunerState();           // edge-detect DSP tuner engage/exit and navigate accordingly
    void gotoScreenById(ScreenId id);  // dispatch a ScreenId to the matching generated transition

    ScreenId currentScreenId;   // which screen is showing right now
    ScreenId returnScreenId;    // where to go when the tuner disengages
    bool     inTunerMode;       // true while parked on the tuning screen because of the DSP
    uint16_t tickCounter_u16;   // throttle for the tuner I2C poll (footswitch changes slowly)
};

#endif // FRONTENDAPPLICATION_HPP
