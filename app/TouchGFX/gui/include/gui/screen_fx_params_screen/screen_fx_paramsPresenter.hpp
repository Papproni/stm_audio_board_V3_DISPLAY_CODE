#ifndef SCREEN_FX_PARAMSPRESENTER_HPP
#define SCREEN_FX_PARAMSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_fx_paramsView;

class screen_fx_paramsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_fx_paramsPresenter(screen_fx_paramsView& v);

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

    virtual ~screen_fx_paramsPresenter() {}

    virtual void set_sliders_value(uint32_t* val);
private:
    screen_fx_paramsPresenter();

    screen_fx_paramsView& view;
};

#endif // SCREEN_FX_PARAMSPRESENTER_HPP
