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
