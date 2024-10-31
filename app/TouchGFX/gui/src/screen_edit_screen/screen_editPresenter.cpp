#include <gui/screen_edit_screen/screen_editView.hpp>
#include <gui/screen_edit_screen/screen_editPresenter.hpp>

screen_editPresenter::screen_editPresenter(screen_editView& v)
    : view(v)
{

}

void screen_editPresenter::activate()
{
#ifndef SIMULATOR
    model->read_loopbypass();
#endif
}

void screen_editPresenter::deactivate()
{

}

void screen_editPresenter::update_screen()
{
#ifndef SIMULATOR
    view.loopbypass = model->get_loopbypass();
#endif
	view.update_screen();
}

#ifndef SIMULATOR
void screen_editPresenter::set_current_loop_num(uint8_t loopnum){
    model->set_current_loop_num(loopnum);
}
void screen_editPresenter::set_current_fx_slot_num(uint8_t slotnum){
    model->set_current_fx_slot_num(slotnum);
}
#endif


// 0: L12 
// 1: L23
// 2: L34
void screen_editPresenter::set_loopbypass(uint8_t loop, uint8_t state)
{
#ifndef SIMULATOR
    model->set_loopbypass(loop,state);
#endif   
}

void screen_editPresenter::read_loopdata(uint8_t loopnum){
#ifndef SIMULATOR
    model->read_loop_data(loopnum);
#endif   
}