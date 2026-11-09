#include <gui/screen_perf_mode_screen/screen_perf_modeView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
screen_perf_modeView::screen_perf_modeView()
{

}

void screen_perf_modeView::setupScreen()
{
    screen_perf_modeViewBase::setupScreen();
}

void screen_perf_modeView::tearDownScreen()
{
    screen_perf_modeViewBase::tearDownScreen();
}

void screen_perf_modeView::update_screen()
{
    uint8_t major_u8 ='Z';
    uint8_t minor_u8 = 9;
    uint8_t mode_u8  = 0;
    sab_loopbypass_tun loopbypass_un;
    memset(&loopbypass_un, 0, sizeof(loopbypass_un));
    #ifndef SIMULATOR
        major_u8 = this->preset_data_un.preset_Major_u8;
        minor_u8 = this->preset_data_un.preset_Minor_u8;
        mode_u8  = this->preset_data_un.fx_active_mode_u8;
        loopbypass_un = this->loopbypass_un;
    #endif
    // Change major character
    Unicode::snprintf(text_preset_num_majorBuffer,TEXT_PRESET_NUM_MAJOR_SIZE,"%c",major_u8);
    Unicode::snprintf(text_preset_num_minorBuffer,TEXT_PRESET_NUM_MINOR_SIZE,"%d",minor_u8);
    
    text_preset_num_major.resizeToCurrentText();
    text_preset_num_major.invalidate();
    text_preset_num_minor.resizeToCurrentText();
    text_preset_num_minor.invalidate();

    // Header: light active loop-bypass boxes + active mode box
    mode_header_container1.update(loopbypass_un, mode_u8);
}
