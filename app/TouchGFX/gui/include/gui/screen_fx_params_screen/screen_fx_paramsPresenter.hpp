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

    void get_fx_param_data();

    virtual ~screen_fx_paramsPresenter() {}

    void getFxname(char* data);

    virtual void update_screen();
private:
    screen_fx_paramsPresenter();

    screen_fx_paramsView& view;
};

#endif // SCREEN_FX_PARAMSPRESENTER_HPP
