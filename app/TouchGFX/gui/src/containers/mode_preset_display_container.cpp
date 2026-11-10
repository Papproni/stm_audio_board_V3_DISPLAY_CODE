#include <gui/containers/mode_preset_display_container.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

mode_preset_display_container::mode_preset_display_container()
{

}

void mode_preset_display_container::initialize()
{
    mode_preset_display_containerBase::initialize();

    // The generated text_curr_preset is a static placeholder; replace it with a
    // dynamic wildcard area so the current preset number can be shown at runtime.
    remove(text_curr_preset);
    text_curr_preset_dyn.setXY(22, 0);
    text_curr_preset_dyn.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    text_curr_preset_dyn.setLinespacing(0);
    // TypedText must contain a <placeholder> (ASCII 2) for the wildcard to render in.
    // T_FXNAME_BUFFER is "<>" with Verdana 20 — same size as the original placeholder.
    text_curr_preset_dyn.setTypedText(touchgfx::TypedText(T_FXNAME_BUFFER));
    Unicode::snprintf(curr_preset_buf, 4, "%c%d", 'Z', 9);
    text_curr_preset_dyn.setWildcard(curr_preset_buf);
    text_curr_preset_dyn.resizeToCurrentText();
    add(text_curr_preset_dyn);
}

void mode_preset_display_container::set_current_preset(uint8_t major_u8, uint8_t minor_u8)
{
    Unicode::snprintf(curr_preset_buf, 4, "%c%d", major_u8, minor_u8);
    text_curr_preset_dyn.setWildcard(curr_preset_buf);
    text_curr_preset_dyn.resizeToCurrentText();
    text_curr_preset_dyn.invalidate();
}

void mode_preset_display_container::set_active_mode(uint8_t fx_active_mode_u8)
{
    const uint8_t ALPHA_ON  = 255;
    const uint8_t ALPHA_OFF = 60;

    // Box::setAlpha() does not mark the widget dirty — invalidate, or stale
    // regions keep their old alpha until something else redraws them.
    auto apply_alpha = [](touchgfx::Box& box, uint8_t new_alpha){
        box.setAlpha(new_alpha);
        box.invalidate();
    };

    // fx_active_mode_u8 mirrors the DSP fx_active_modes_ten enum: 0=A, 1=B, 2=C, 3=D
    apply_alpha(mode_A_bgnd, fx_active_mode_u8 == 0 ? ALPHA_ON : ALPHA_OFF);
    apply_alpha(mode_B_bgnd, fx_active_mode_u8 == 1 ? ALPHA_ON : ALPHA_OFF);
    apply_alpha(mode_C_bgnd, fx_active_mode_u8 == 2 ? ALPHA_ON : ALPHA_OFF);
    apply_alpha(mode_D_bgnd, fx_active_mode_u8 == 3 ? ALPHA_ON : ALPHA_OFF);
}
