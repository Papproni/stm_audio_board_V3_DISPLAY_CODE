#include <gui/screen_fx_params_screen/screen_fx_paramsView.hpp>
#include <touchgfx/Color.hpp>
#include "math.h"


screen_fx_paramsView::screen_fx_paramsView()
{
	// set default potvalues
	this->potmeter_scale_value 	= -280;
	this->potmeter_min_value 	= -140;
	this->potmeter_offset_value = 140;
	this->adc_raw_max_value		= pow(2,16)-1;



	// Change background color
	MAIN_BACKGROUND.setColor(touchgfx::Color::getColorFromRGB(100, 30, 70));
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

}

void screen_fx_paramsView::tearDownScreen()
{
    screen_fx_paramsViewBase::tearDownScreen();

}

int screen_fx_paramsView::convert_adc_to_pot_values(int val)
{
	return (double)val/(double)this->adc_raw_max_value*this->potmeter_scale_value+this->potmeter_offset_value;
}

void screen_fx_paramsView::set_sliders_value(uint32_t* val)
{

//	ParamSlot1.invalidate();
    ParamSlot1.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[0]));
//    ParamSlot1.invalidate();

//    ParamSlot2.invalidate();
	ParamSlot2.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[1]));
//	ParamSlot2.invalidate();

//	ParamSlot3.invalidate();
	ParamSlot3.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[2]));
//	ParamSlot3.invalidate();

//	ParamSlot4.invalidate();
	ParamSlot4.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[3]));
//	ParamSlot4.invalidate();

//	ParamSlot5.invalidate();
	ParamSlot5.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[4]));
//	ParamSlot5.invalidate();

//	ParamSlot6.invalidate();
	ParamSlot6.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[5]));
//	ParamSlot6.invalidate();

	swipeContainer.invalidate();
}
