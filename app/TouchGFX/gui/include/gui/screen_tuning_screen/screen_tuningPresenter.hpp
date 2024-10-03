#ifndef SCREEN_TUNINGPRESENTER_HPP
#define SCREEN_TUNINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_tuningView;

class screen_tuningPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_tuningPresenter(screen_tuningView& v);

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

    virtual ~screen_tuningPresenter() {}

private:
    screen_tuningPresenter();

    screen_tuningView& view;
};

#endif // SCREEN_TUNINGPRESENTER_HPP
