#include <gui/screen_tuning_screen/screen_tuningView.hpp>

screen_tuningView::screen_tuningView()
{
}

void screen_tuningView::update_screen()
{
    // Simulator: fixed value. Hardware: live data pushed in by the presenter.
    float   freq_f32  = 440.0f;
    uint8_t active_u8 = 1;
    #ifndef SIMULATOR
        freq_f32  = this->tuner_un.freq_f32;
        active_u8 = this->tuner_un.active_u8;
    #endif

    if ((active_u8 != 0) && (freq_f32 > 40.0f) && (freq_f32 < 6000.0f))
    {
        Unicode::snprintfFloat(text_freqBuffer, TEXT_FREQ_SIZE, "%.3f", freq_f32);
    }
    else
    {
        text_freqBuffer[0] = '-';
        text_freqBuffer[1] = '-';
        text_freqBuffer[2] = 0;
    }

    text_freq.resizeToCurrentText();
    text_freq.invalidate();
}
