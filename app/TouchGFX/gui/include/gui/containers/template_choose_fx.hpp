#ifndef TEMPLATE_CHOOSE_FX_HPP
#define TEMPLATE_CHOOSE_FX_HPP

#include <gui_generated/containers/template_choose_fxBase.hpp>

class template_choose_fx : public template_choose_fxBase
{
public:
    
    template_choose_fx();
    virtual ~template_choose_fx() {}

    virtual void initialize();

    touchgfx::Unicode::UnicodeChar* get_buffer();
    touchgfx::TextAreaWithOneWildcard get_text_wc();
protected:
};

#endif // TEMPLATE_CHOOSE_FX_HPP
