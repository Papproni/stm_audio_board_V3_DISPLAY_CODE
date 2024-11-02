#include <gui/screen_fx_params_screen/screen_fx_paramsView.hpp>
#include <touchgfx/Color.hpp>
#include "math.h"

#ifdef SIMULATOR
#include <touchgfx/Utils.hpp>
#endif


screen_fx_paramsView::screen_fx_paramsView()
{
	// set default potvalues
	this->potmeter_scale_value 	= -280;
	this->potmeter_min_value 	= -140;
	this->potmeter_offset_value = 140;
	this->adc_raw_max_value		= pow(2,16)-1;

}

void screen_fx_paramsView::setupScreen()
{
	// Change name
	FXname.invalidate();

	char stuff[20] = "CustomFX1";
	presenter->getFxname(stuff);

	Unicode::strncpy(FXnameBuffer, stuff, FXNAME_SIZE);
	FXname.resizeToCurrentText();
	FXname.invalidate();

	swipeContainer.setSwipeCutoff(20);

    screen_fx_paramsViewBase::setupScreen();

	my_potmeter.setXY(10, 40);
    swipeContainerPage1.add(my_potmeter);
	
	my_button.setXY(50, 40);
	swipeContainerPage1.add(my_button);
	
	fx_controls_p[0] = &template_fx_param_pot1;
	fx_controls_p[1] = &template_fx_param_pot2;
	fx_controls_p[2] = &template_fx_param_pot3;
	fx_controls_p[3] = &template_fx_param_pot4;
	fx_controls_p[4] = &template_fx_param_pot5;
	fx_controls_p[5] = &template_fx_param_pot6;
	fx_controls_p[6] = &template_fx_param_pot7;
	fx_controls_p[7] = &template_fx_param_pot8;
	fx_controls_p[8] = &template_fx_param_pot9;
	fx_controls_p[9] = &template_fx_param_pot10;
	fx_controls_p[10] = &template_fx_param_pot11;
	fx_controls_p[11] = &template_fx_param_pot12;

	presenter->get_fx_param_data();
	for(int i = 0;i<12;i++){
#ifndef SIMULATOR
		fx_controls_p[i]->init_potmeter((char*)fx_params_tun[i].name,5,fx_params_tun[i].value_u8);
#endif
	}

#ifdef SIMULATOR
#endif
}

void screen_fx_paramsView::tearDownScreen()
{
    screen_fx_paramsViewBase::tearDownScreen();

}



void screen_fx_paramsView::set_sliders_value(uint32_t* val)
{
    // ParamSlot1.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[0]));
	// ParamSlot2.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[1]));
	// ParamSlot3.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[2]));
	// ParamSlot4.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[3]));
	// ParamSlot5.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[4]));
	// ParamSlot6.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[5]));
	
}

void screen_fx_paramsView::update_screen(){
	// TODO
#ifndef SIMULATOR
	for(int i = 0;i<12;i++){
		fx_controls_p[i]->update_potmeter(adc_vals_ptr[i%6]);
	}
	swipeContainer.invalidate();
#endif

#ifdef SIMULATOR
	for(int i = 0;i<12;i++){
		fx_controls_p[i]->update_potmeter(11000);
	}
	swipeContainer.invalidate();
#endif
}
