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

    // Declaring callback handler for Box
    void boxClickHandler(const Line& b, const ClickEvent& e);
    void setAlphaOfContainer(Container &conti,uint8_t alpha);
protected:
    // Declaring callback type of box and clickEvent
    Callback<screen_editView, const Line&, const ClickEvent&> boxClickedCallback;
};

#endif // SCREEN_EDITVIEW_HPP
