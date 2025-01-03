/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN_ADD_EFFECTVIEWBASE_HPP
#define SCREEN_ADD_EFFECTVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen_add_effect_screen/screen_add_effectPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/mixins/ClickListener.hpp>
#include <touchgfx/containers/scrollers/ScrollList.hpp>
#include <gui/containers/template_choose_fx.hpp>

class screen_add_effectViewBase : public touchgfx::View<screen_add_effectPresenter>
{
public:
    screen_add_effectViewBase();
    virtual ~screen_add_effectViewBase();
    virtual void setupScreen();

    virtual void scrollList_FXUpdateItem(template_choose_fx& item, int16_t itemIndex)
    {
        // Override and implement this function in screen_add_effect
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::TextArea text_title;
    touchgfx::ClickListener< touchgfx::ButtonWithLabel > btn_opt;
    touchgfx::ClickListener< touchgfx::ButtonWithLabel > btn_add;
    touchgfx::ScrollList scrollList_FX;
    touchgfx::DrawableListItems<template_choose_fx, 3> scrollList_FXListItems;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<screen_add_effectViewBase, touchgfx::DrawableListItemsInterface*, int16_t, int16_t> updateItemCallback;
    touchgfx::Callback<screen_add_effectViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex);
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SCREEN_ADD_EFFECTVIEWBASE_HPP
