#ifndef MODE_PRESET_DISPLAY_CONTAINER_HPP
#define MODE_PRESET_DISPLAY_CONTAINER_HPP

#include <gui_generated/containers/mode_preset_display_containerBase.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/Unicode.hpp>

class mode_preset_display_container : public mode_preset_display_containerBase
{
public:
    mode_preset_display_container();
    virtual ~mode_preset_display_container() {}

    virtual void initialize();

    // Show the current preset number (major letter + minor digit, e.g. "A3") in text_curr_preset
    void set_current_preset(uint8_t major_u8, uint8_t minor_u8);

    // Light the mode box matching fx_active_mode_u8 (0=A, 1=B, 2=C, 3=D) and dim the rest,
    // mirroring mode_header_container's mode-box highlighting.
    void set_active_mode(uint8_t fx_active_mode_u8);

protected:
    // Replaces the static generated placeholder so the value can change at runtime
    touchgfx::TextAreaWithOneWildcard text_curr_preset_dyn;
    touchgfx::Unicode::UnicodeChar curr_preset_buf[4];
};

#endif // MODE_PRESET_DISPLAY_CONTAINER_HPP
