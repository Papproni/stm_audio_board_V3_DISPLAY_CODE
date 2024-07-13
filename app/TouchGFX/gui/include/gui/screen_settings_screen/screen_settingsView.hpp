#ifndef SCREEN_SETTINGSVIEW_HPP
#define SCREEN_SETTINGSVIEW_HPP

#include <gui_generated/screen_settings_screen/screen_settingsViewBase.hpp>
#include <gui/screen_settings_screen/screen_settingsPresenter.hpp>

class screen_settingsView : public screen_settingsViewBase
{
public:
    screen_settingsView();
    virtual ~screen_settingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_SETTINGSVIEW_HPP
