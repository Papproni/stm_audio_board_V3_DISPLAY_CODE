#include <gui/screen_tuning_screen/screen_tuningView.hpp>
#include <math.h>

// Note names in pitch-class order. Flat accidentals (Db/Eb/Gb/Ab/Bb) are used
// because the note-label font has no '#' glyph -- sharps would render as '?'.
// Every name is padded to exactly TWO characters with a trailing space so the
// label widgets keep a constant width. Shrinking a 2-char name to 1 char
// ("Ab" -> "A") left stale pixels behind and the old note kept showing; a fixed
// width means the widget never resizes, so invalidate() always repaints cleanly.
static const char* NOTE_NAMES[12] = {
    "C ", "Db", "D ", "Eb", "E ", "F ", "Gb", "G ", "Ab", "A ", "Bb", "B "
};

#define TUNER_C_REF_HZ   130.81f  // C3, base note of the table (octave folding reference)
#define NEEDLE_HALF_DEG  3        // half-width of the red needle arc, in degrees
#define NEEDLE_FS_CENTS  50.0f    // cents at which the needle reaches a gauge end

// Copy a short ASCII note name into a wildcard buffer and refresh the widget.
static void set_note_label(touchgfx::TextAreaWithOneWildcard& area,
                           touchgfx::Unicode::UnicodeChar* buf, uint16_t size, const char* name)
{
    // Invalidate at the CURRENT size before writing new text. If the new note is
    // shorter than the old one (e.g. "Ab" -> "A"), this captures the full previous
    // width in the dirty region so the background behind repaints over any stale
    // glyph pixels the shorter text won't cover — without it, shrinking notes kept
    // showing the old trailing letter ("Ab Ab Bb" at 110 Hz). The 2-char-padded
    // names below keep the width constant as a second layer of protection.
    area.invalidate();
    uint16_t i = 0;
    while ((name[i] != 0) && (i + 1 < size)) { buf[i] = (touchgfx::Unicode::UnicodeChar)(unsigned char)name[i]; i++; }
    buf[i] = 0;
    area.resizeToCurrentText();
    area.invalidate();
}

screen_tuningView::screen_tuningView()
{
    last_pc_s8          = -1;
    last_needle_deg_s16 = 1000;
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

        // Octave-aware nearest note: fold any octave into the C..B pitch classes.
        float semis = log2f(freq_f32 / TUNER_C_REF_HZ) * 12.0f; // continuous semitones above C
        int   idx   = (int)(floorf(semis + 0.5f));              // nearest note, any octave
        int   pc    = ((idx % 12) + 12) % 12;                   // pitch class 0..11
        float cents = (semis - (float)idx) * 100.0f;            // deviation in cents, ~[-50,+50]

        // Note labels: repaint only when the pitch class changes.
        if ((int8_t)pc != last_pc_s8)
        {
            set_note_label(text_note_middle, text_note_middleBuffer, TEXT_NOTE_MIDDLE_SIZE, NOTE_NAMES[pc]);
            set_note_label(text_note_higher, text_note_higherBuffer, TEXT_NOTE_HIGHER_SIZE, NOTE_NAMES[(pc + 1) % 12]);
            set_note_label(text_note_lower,  text_note_lowerBuffer,  TEXT_NOTE_LOWER_SIZE,  NOTE_NAMES[(pc + 11) % 12]);
            last_pc_s8 = (int8_t)pc;
        }

        // Red needle: cents -> angle. 0 deg = top (in tune), +right sharp, -left flat.
        float deg_f = cents * (90.0f / NEEDLE_FS_CENTS);        // 1.8 deg per cent
        if (deg_f >  90.0f) { deg_f =  90.0f; }
        if (deg_f < -90.0f) { deg_f = -90.0f; }
        int deg = (int)(floorf(deg_f + (deg_f >= 0.0f ? 0.5f : -0.5f)));
        if (deg != last_needle_deg_s16)
        {
            tuning_current_loc.updateArc((deg - NEEDLE_HALF_DEG), (deg + NEEDLE_HALF_DEG));
            last_needle_deg_s16 = deg;
        }
    }
    else
    {
        // No valid signal: dash readout, dash notes, needle parked at center.
        text_freqBuffer[0] = '-';
        text_freqBuffer[1] = '-';
        text_freqBuffer[2] = 0;

        if (last_pc_s8 != -1)
        {
            set_note_label(text_note_middle, text_note_middleBuffer, TEXT_NOTE_MIDDLE_SIZE, "- ");
            set_note_label(text_note_higher, text_note_higherBuffer, TEXT_NOTE_HIGHER_SIZE, "- ");
            set_note_label(text_note_lower,  text_note_lowerBuffer,  TEXT_NOTE_LOWER_SIZE,  "- ");
            last_pc_s8 = -1;
        }

        if (last_needle_deg_s16 != 0)
        {
            tuning_current_loc.updateArc(-NEEDLE_HALF_DEG, NEEDLE_HALF_DEG);
            last_needle_deg_s16 = 0;
        }
    }

    text_freq.resizeToCurrentText();
    text_freq.invalidate();
}
