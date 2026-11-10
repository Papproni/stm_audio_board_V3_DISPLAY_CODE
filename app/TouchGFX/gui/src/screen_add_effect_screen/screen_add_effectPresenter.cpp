#include <gui/screen_add_effect_screen/screen_add_effectView.hpp>
#include <gui/screen_add_effect_screen/screen_add_effectPresenter.hpp>
#include <gui/model/Model.hpp>
#include <stdlib.h>

screen_add_effectPresenter::screen_add_effectPresenter(screen_add_effectView &v)
    : view(v), last_preset_major_u8(0xFF), last_preset_minor_u8(0xFF), scroll_index(0), num_effects(0)
{
#ifndef SIMULATOR
	view.implemented_fx_ptr = NULL;
	view.num_of_implemented_fx = 0;
#endif

}

void screen_add_effectPresenter::activate()
{
#ifndef SIMULATOR
    view.num_of_implemented_fx = model->get_num_of_implemented_fx();
    view.implemented_fx_ptr = model->get_implemented_fx();
    this->loop_data = model->get_loop_data(model->get_current_loop_num());
    num_effects = view.num_of_implemented_fx;
#else
    num_effects = 4; // matches the SIMULATOR list size in screen_add_effectView::update_screen()
#endif
    scroll_index = 0;
}

void screen_add_effectPresenter::deactivate()
{
}

void screen_add_effectPresenter::add_effect(uint8_t choosen_fx)
{
#ifndef SIMULATOR
    fx_data_tst *fx_ptr;
    switch (model->get_current_fx_slot_num())
    {
    case FX_SLOT1:
        fx_ptr = &this->loop_data.slot1;
        break;
    case FX_SLOT2:
        fx_ptr = &this->loop_data.slot2;
        break;
    case FX_SLOT3:
        fx_ptr = &this->loop_data.slot3;
        break;

    default:
        break;
    }

    strcpy(fx_ptr->name, view.implemented_fx_ptr[choosen_fx].name);
    for (int i = 0; i < 3; i++)
    {
        fx_ptr->color[i] = view.implemented_fx_ptr[choosen_fx].color[i];
    }

    model->set_loop_data(&this->loop_data);
#endif
}

void screen_add_effectPresenter::add_current_effect()
{
#ifndef SIMULATOR
    if (num_effects <= 0)
    {
        return;
    }
    int16_t idx = scroll_index;
    if (idx < 0)
    {
        idx = 0;
    }
    if (idx > num_effects - 1)
    {
        idx = (int16_t)(num_effects - 1);
    }
    add_effect((uint8_t)idx);
    view.return_to_loop_screen();
#endif
}

void screen_add_effectPresenter::update_screen()
{
#ifndef SIMULATOR
    // If the preset number changes while adding an effect, go back to the loop screen —
    // a new preset can have a different effect setup than the one being edited.
    model->read_preset_data();
    sab_preset_num_tun pst = model->get_preset_data();
    if (last_preset_major_u8 != 0xFF &&
        (pst.preset_Major_u8 != last_preset_major_u8 || pst.preset_Minor_u8 != last_preset_minor_u8))
    {
        view.return_to_loop_screen();
        return;
    }
    last_preset_major_u8 = pst.preset_Major_u8;
    last_preset_minor_u8 = pst.preset_Minor_u8;
#endif // ! SIMULATOR

#ifndef SIMULATOR
    // Pot 0 drives the effect carousel. Its full 16-bit range is mapped across the effects so
    // turning it left -> right walks first -> last, keeping the selected effect centered.
    if (num_effects > 1 && model->get_adc_value_ptr() != NULL)
    {
        uint32_t pot = model->get_adc_value_ptr()[0];
        if (pot > 65535u)
        {
            pot = 65535u;
        }
        // round(pot/65535 * (num_effects-1)) in integer math: (a + b/2)/b with a=pot*(N-1), b=65535
        int16_t idx = (int16_t)(((uint32_t)(65535u - pot) * (num_effects - 1) + 32767u) / 65535u);
        if (idx > num_effects - 1)
        {
            idx = num_effects - 1;
        }
        if (idx != scroll_index)
        {
            scroll_index = idx;
            view.set_scroll_index(scroll_index);
        }
    }
#endif // ! SIMULATOR

    view.update_screen();
}
