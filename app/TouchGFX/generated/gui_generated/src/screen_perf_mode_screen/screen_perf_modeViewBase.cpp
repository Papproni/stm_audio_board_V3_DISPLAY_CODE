/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen_perf_mode_screen/screen_perf_modeViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>

screen_perf_modeViewBase::screen_perf_modeViewBase() :
    buttonCallback(this, &screen_perf_modeViewBase::buttonCallbackHandler)
{
    __background.setPosition(0, 0, 320, 240);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    MAIN_BACKGROUND.setPosition(0, 0, 320, 240);
    MAIN_BACKGROUND.setColor(touchgfx::Color::getColorFromRGB(0, 98, 255));
    add(MAIN_BACKGROUND);

    text_preset_num_minor.setXY(174, 19);
    text_preset_num_minor.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    text_preset_num_minor.setLinespacing(0);
    Unicode::snprintf(text_preset_num_minorBuffer, TEXT_PRESET_NUM_MINOR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_YG4D).getText());
    text_preset_num_minor.setWildcard(text_preset_num_minorBuffer);
    text_preset_num_minor.resizeToCurrentText();
    text_preset_num_minor.setTypedText(touchgfx::TypedText(T___SINGLEUSE_1IH8));
    add(text_preset_num_minor);

    text_preset_num_major.setXY(30, 19);
    text_preset_num_major.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    text_preset_num_major.setLinespacing(0);
    Unicode::snprintf(text_preset_num_majorBuffer, TEXT_PRESET_NUM_MAJOR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_322K).getText());
    text_preset_num_major.setWildcard(text_preset_num_majorBuffer);
    text_preset_num_major.resizeToCurrentText();
    text_preset_num_major.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8Z2S));
    add(text_preset_num_major);

    btn_opt.setXY(0, 0);
    btn_opt.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_FILL_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_FILL_DISABLED_ID));
    btn_opt.setLabelText(touchgfx::TypedText(T___SINGLEUSE_4F5J));
    btn_opt.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    btn_opt.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    btn_opt.setAction(buttonCallback);
    add(btn_opt);
}

screen_perf_modeViewBase::~screen_perf_modeViewBase()
{

}

void screen_perf_modeViewBase::setupScreen()
{

}

void screen_perf_modeViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &btn_opt)
    {
        //ToSettings
        //When btn_opt clicked change screen to screen_settings
        //Go to screen_settings with no screen transition
        application().gotoscreen_settingsScreenNoTransition();
    }
}
