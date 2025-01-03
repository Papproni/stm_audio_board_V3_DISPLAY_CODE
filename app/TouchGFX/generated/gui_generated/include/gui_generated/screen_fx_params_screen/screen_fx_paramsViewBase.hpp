/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN_FX_PARAMSVIEWBASE_HPP
#define SCREEN_FX_PARAMSVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen_fx_params_screen/screen_fx_paramsPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/SwipeContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <gui/containers/template_fx_param.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class screen_fx_paramsViewBase : public touchgfx::View<screen_fx_paramsPresenter>
{
public:
    screen_fx_paramsViewBase();
    virtual ~screen_fx_paramsViewBase();
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box MAIN_BACKGROUND;
    touchgfx::SwipeContainer swipeContainer;
    touchgfx::Container swipeContainerPage1;
    touchgfx::Box MAIN_BACKGROUND_1;
    template_fx_param template_fx_param1;
    template_fx_param template_fx_param2;
    template_fx_param template_fx_param3;
    template_fx_param template_fx_param4;
    template_fx_param template_fx_param5;
    template_fx_param template_fx_param6;
    touchgfx::Container swipeContainerPage2;
    touchgfx::Box MAIN_BACKGROUND_1_1;
    template_fx_param template_fx_param12;
    template_fx_param template_fx_param11;
    template_fx_param template_fx_param10;
    template_fx_param template_fx_param9;
    template_fx_param template_fx_param8;
    template_fx_param template_fx_param7;
    touchgfx::TextAreaWithOneWildcard FXname;
    touchgfx::ButtonWithLabel btn_back;

    /*
     * Wildcard Buffers
     */
    static const uint16_t FXNAME_SIZE = 15;
    touchgfx::Unicode::UnicodeChar FXnameBuffer[FXNAME_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 4800;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

    /*
     * Callback Declarations
     */
    touchgfx::Callback<screen_fx_paramsViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SCREEN_FX_PARAMSVIEWBASE_HPP
