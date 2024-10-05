#ifndef SCREEN_EDITVIEW_HPP
#define SCREEN_EDITVIEW_HPP

#include <gui_generated/screen_edit_screen/screen_editViewBase.hpp>
#include <gui/screen_edit_screen/screen_editPresenter.hpp>

class screen_editView : public screen_editViewBase
{
public:
    screen_editView();
    virtual ~screen_editView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void update_screen();
protected:
};

#endif // SCREEN_EDITVIEW_HPP
