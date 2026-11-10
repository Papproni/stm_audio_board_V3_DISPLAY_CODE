#include <gui/common/FrontendApplication.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap),
      currentScreenId(SCR_STARTUP),
      returnScreenId(SCR_LOOP),
      inTunerMode(false),
      tickCounter_u16(0)
{
}

void FrontendApplication::handleTickEvent()
{
    // Poll the DSP tuner state first so a newly-entered tuning screen is refreshed on this same
    // tick; then let the model update the active presenter and the base evaluate pending transitions.
    pollTunerState();
    model.tick();
    FrontendApplicationBase::handleTickEvent();
}

void FrontendApplication::pollTunerState()
{
    // The tuner footswitch is latching and changes slowly, so sample the I2C register at a reduced
    // rate instead of every tick to keep the bus free for the data screens.
    if (++tickCounter_u16 < 5)
    {
        return;
    }
    tickCounter_u16 = 0;

    model.read_tuner_data();
    bool active = (model.get_tuner_data().active_u8 != 0);

    if (active && !inTunerMode)
    {
        // Rising edge: DSP engaged the tuner. Remember where we were and jump to the tuning screen.
        returnScreenId = currentScreenId;
        inTunerMode = true;
        gotoscreen_tuningScreenNoTransition();   // our shadow records SCR_TUNING
    }
    else if (!active && inTunerMode)
    {
        // Falling edge: DSP exited the tuner. Return to the screen that was showing before.
        inTunerMode = false;
        gotoScreenById(returnScreenId);
    }
}

void FrontendApplication::gotoScreenById(ScreenId id)
{
    switch (id)
    {
        case SCR_STARTUP:     gotoscreen_startupScreenNoTransition();     break;
        case SCR_SETTINGS:    gotoscreen_settingsScreenNoTransition();    break;
        case SCR_TUNING:      gotoscreen_tuningScreenNoTransition();      break;
        case SCR_PERF_MODE:   gotoscreen_perf_modeScreenNoTransition();   break;
        case SCR_INFO:        gotoscreen_infoScreenNoTransition();        break;
        case SCR_FX_PARAMS:   gotoscreen_fx_paramsScreenNoTransition();   break;
        case SCR_CONFIG:      gotoscreen_configScreenNoTransition();      break;
        case SCR_LOOP:        gotoscreen_loopScreenNoTransition();        break;
        case SCR_EDIT:        gotoscreen_editScreenNoTransition();        break;
        case SCR_ADD_EFFECT:  gotoscreen_add_effectScreenNoTransition();  break;
        default:              gotoscreen_loopScreenNoTransition();        break;
    }
}

// --- Navigation shadows: record the active screen, then run the real generated transition. ---
// A manual navigation away from the tuning screen also clears inTunerMode. The tuning goto is the
// one exception: entering it is what establishes tuner mode, so it must not clear the flag.

void FrontendApplication::gotoscreen_startupScreenNoTransition()
{
    currentScreenId = SCR_STARTUP;
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_startupScreenNoTransition();
}

void FrontendApplication::gotoscreen_settingsScreenNoTransition()
{
    currentScreenId = SCR_SETTINGS;
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_settingsScreenNoTransition();
}

void FrontendApplication::gotoscreen_tuningScreenNoTransition()
{
    currentScreenId = SCR_TUNING;   // entering tuning screen: leave inTunerMode as-is
    FrontendApplicationBase::gotoscreen_tuningScreenNoTransition();
}

void FrontendApplication::gotoscreen_perf_modeScreenNoTransition()
{
    currentScreenId = SCR_PERF_MODE;
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_perf_modeScreenNoTransition();
}

void FrontendApplication::gotoscreen_perf_modeScreenCoverTransitionEast()
{
    currentScreenId = SCR_PERF_MODE;   // startup screen reaches perf-mode via this variant
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_perf_modeScreenCoverTransitionEast();
}

void FrontendApplication::gotoscreen_infoScreenNoTransition()
{
    currentScreenId = SCR_INFO;
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_infoScreenNoTransition();
}

void FrontendApplication::gotoscreen_fx_paramsScreenNoTransition()
{
    currentScreenId = SCR_FX_PARAMS;
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_fx_paramsScreenNoTransition();
}

void FrontendApplication::gotoscreen_configScreenNoTransition()
{
    currentScreenId = SCR_CONFIG;
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_configScreenNoTransition();
}

void FrontendApplication::gotoscreen_loopScreenNoTransition()
{
    currentScreenId = SCR_LOOP;
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_loopScreenNoTransition();
}

void FrontendApplication::gotoscreen_editScreenNoTransition()
{
    currentScreenId = SCR_EDIT;
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_editScreenNoTransition();
}

void FrontendApplication::gotoscreen_add_effectScreenNoTransition()
{
    currentScreenId = SCR_ADD_EFFECT;
    inTunerMode = false;
    FrontendApplicationBase::gotoscreen_add_effectScreenNoTransition();
}
