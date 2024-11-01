#include <gui/screen_add_effect_screen/screen_add_effectView.hpp>
#include <gui/screen_add_effect_screen/screen_add_effectPresenter.hpp>

screen_add_effectPresenter::screen_add_effectPresenter(screen_add_effectView &v)
    : view(v)
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
#endif
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

void screen_add_effectPresenter::update_screen()
{
    view.update_screen();
}
