#include <gui/screen_add_effect_screen/screen_add_effectView.hpp>
#include <gui/screen_add_effect_screen/screen_add_effectPresenter.hpp>

screen_add_effectPresenter::screen_add_effectPresenter(screen_add_effectView& v)
    : view(v)
{

}

void screen_add_effectPresenter::activate()
{
    view.num_of_implemented_fx = model->get_num_of_implemented_fx();
    view.implemented_fx_ptr    = model->get_implemented_fx();
}

void screen_add_effectPresenter::deactivate()
{

}

void screen_add_effectPresenter::update_screen(){
    view.update_screen();
}
