#ifndef SCREEN_SETTINGSPRESENTER_HPP
#define SCREEN_SETTINGSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_settingsView;

class screen_settingsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_settingsPresenter(screen_settingsView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~screen_settingsPresenter() {}

private:
    screen_settingsPresenter();

    screen_settingsView& view;
};

#endif // SCREEN_SETTINGSPRESENTER_HPP
