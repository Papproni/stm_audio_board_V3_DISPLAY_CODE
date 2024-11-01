#include <gui/containers/template_choose_fx.hpp>

template_choose_fx::template_choose_fx()
{

}

void template_choose_fx::initialize()
{
    template_choose_fxBase::initialize();
}

touchgfx::Unicode::UnicodeChar*  template_choose_fx::get_buffer(){
    return this->text_FX_nameBuffer;
}

touchgfx::TextAreaWithOneWildcard template_choose_fx::get_text_wc(){
    return this->text_FX_name;
}

touchgfx::TextArea template_choose_fx::get_selected_text(){
    return this->text_selected;
}