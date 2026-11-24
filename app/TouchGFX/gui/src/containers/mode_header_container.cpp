#include <gui/containers/mode_header_container.hpp>

mode_header_container::mode_header_container()
{

}

void mode_header_container::initialize()
{
    mode_header_containerBase::initialize();
}

void mode_header_container::update(const sab_loopbypass_tun& loopbypass_un, uint8_t fx_active_mode_u8)
{
    const uint8_t ALPHA_ON  = 255;
    const uint8_t ALPHA_OFF = 60;

    // Box::setAlpha() does not mark the widget dirty — invalidate, or stale
    // regions keep their old alpha until something else redraws them.
    auto apply_alpha = [](touchgfx::Box& box, uint8_t new_alpha){
        box.setAlpha(new_alpha);
        box.invalidate();
    };

    // Loop boxes: lit when the corresponding loop bypass is active
    apply_alpha(loop1_bgnd, loopbypass_un.L12 ? ALPHA_ON : ALPHA_OFF);
    apply_alpha(loop2_bgnd, loopbypass_un.L23 ? ALPHA_ON : ALPHA_OFF);
    apply_alpha(loop3_bgnd, loopbypass_un.L34 ? ALPHA_ON : ALPHA_OFF);

    // Mode boxes: light the active preset mode.
    // fx_active_mode_u8 mirrors the DSP fx_active_modes_ten enum: 0=A, 1=B, 2=C, 3=D
    apply_alpha(text_mode_A_bgnd, fx_active_mode_u8 == 0 ? ALPHA_ON : ALPHA_OFF);
    apply_alpha(text_mode_B_bgnd, fx_active_mode_u8 == 1 ? ALPHA_ON : ALPHA_OFF);
    apply_alpha(text_mode_C_bgnd, fx_active_mode_u8 == 2 ? ALPHA_ON : ALPHA_OFF);
    apply_alpha(text_mode_D_bgnd, fx_active_mode_u8 == 3 ? ALPHA_ON : ALPHA_OFF);
}
