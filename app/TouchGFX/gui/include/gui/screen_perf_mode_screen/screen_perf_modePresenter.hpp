#ifndef SCREEN_PERF_MODEPRESENTER_HPP
#define SCREEN_PERF_MODEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_perf_modeView;

class screen_perf_modePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_perf_modePresenter(screen_perf_modeView& v);

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

    virtual ~screen_perf_modePresenter() {}

private:
    screen_perf_modePresenter();

    screen_perf_modeView& view;
};

#endif // SCREEN_PERF_MODEPRESENTER_HPP
