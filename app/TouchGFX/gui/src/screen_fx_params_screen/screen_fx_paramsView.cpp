#include <gui/screen_fx_params_screen/screen_fx_paramsView.hpp>
#include <touchgfx/Color.hpp>
#include "math.h"

#ifdef SIMULATOR
#include <touchgfx/Utils.hpp>
#endif

screen_fx_paramsView::screen_fx_paramsView()
{
	// set default potvalues
	this->potmeter_scale_value = -280;
	this->potmeter_min_value = -140;
	this->potmeter_offset_value = 140;
	this->adc_raw_max_value = pow(2, 16) - 1;

	// this->parameter_positions_au8[0][0]

	// template_fx_param_pot6.setXY(200, 130);
	// template_fx_param_pot5.setXY(120, 130);
	// template_fx_param_pot4.setXY(40, 130);
	// template_fx_param_pot3.setXY(200, 40);
	// template_fx_param_pot2.setXY(120, 40);
	// template_fx_param_pot1.setXY(40, 40);
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

	fx_controls_p[0] = &template_fx_param1;
	fx_controls_p[1] = &template_fx_param2;
	fx_controls_p[2] = &template_fx_param3;
	fx_controls_p[3] = &template_fx_param4;
	fx_controls_p[4] = &template_fx_param5;
	fx_controls_p[5] = &template_fx_param6;
	fx_controls_p[6] = &template_fx_param7;
	fx_controls_p[7] = &template_fx_param8;
	fx_controls_p[8] = &template_fx_param9;
	fx_controls_p[9] = &template_fx_param10;
	fx_controls_p[10] = &template_fx_param11;
	fx_controls_p[11] = &template_fx_param12;

	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLLUMS; j++)
		{
			this->parameter_positions_au8[i + i * NUM_OF_ROWS + j][0] = START_LOC + j * COLLUM_WIDTH;
			this->parameter_positions_au8[i + i * NUM_OF_ROWS + j][1] = START_LOC + i * ROW_HEIGHT;
		}
	}

	presenter->get_fx_param_data();
	for (int i = 0; i < NUM_OF_PARAM_PAGES; i++)
	{
		for (int j = 0; j < NUM_OF_PARAMS_PER_PAGE; j++)
		{
			int idx = i * NUM_OF_PARAMS_PER_PAGE + j;
			uint8_t x = this->parameter_positions_au8[j][0];
			uint8_t y = this->parameter_positions_au8[j][1];
			fx_controls_p[idx]->invalidate();
#ifndef SIMULATOR
			fx_controls_p[idx]->init_parameter((char *)fx_params_tun[i].name, 5, fx_params_tun[i].type_en, fx_params_tun[i].value_u8);
#endif
			fx_controls_p[idx]->setXY(x, y);
			fx_controls_p[idx]->invalidate();
		}
	}

#ifdef SIMULATOR
	param_type_ten type = PARAM_TYPE_POT;
	fx_controls_p[0]->init_parameter("LOW", 5, type, 100);
	fx_controls_p[0]->invalidate();
	fx_controls_p[1]->init_parameter("MID", 5, type, 200);
	fx_controls_p[1]->invalidate();
	fx_controls_p[2]->init_parameter("TOP", 5, type, 70);
	fx_controls_p[2]->invalidate();
	type = PARAM_TYPE_BTN;
	fx_controls_p[3]->init_parameter("MOD", 5, type, 1);
	fx_controls_p[3]->invalidate();
	fx_controls_p[4]->init_parameter("TAP", 5, type, 0);
	fx_controls_p[4]->invalidate();
	type = PARAM_TYPE_UNUSED;
	fx_controls_p[5]->init_parameter("N/A", 5, type, 0);
	fx_controls_p[5]->invalidate();
	fx_controls_p[6]->init_parameter("N/A", 5, type, 0);
	fx_controls_p[6]->invalidate();
#endif
}

void screen_fx_paramsView::tearDownScreen()
{
	screen_fx_paramsViewBase::tearDownScreen();
}

void screen_fx_paramsView::set_sliders_value(uint32_t *val)
{
	// ParamSlot1.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[0]));
	// ParamSlot2.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[1]));
	// ParamSlot3.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[2]));
	// ParamSlot4.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[3]));
	// ParamSlot5.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[4]));
	// ParamSlot6.setArc(this->potmeter_min_value, convert_adc_to_pot_values(val[5]));
}

void screen_fx_paramsView::update_screen()
{
	// TODO
#ifndef SIMULATOR
	for (int i = 0; i < 12; i++)
	{
		if (fx_controls_p[i]->update_ui(adc_vals_ptr[i % 6]))
		{
			// needs offset by 1 in slotnum!
			presenter->set_fx_param_new_value(i+1, fx_controls_p[i]->get_param_value());
		}
	}
	swipeContainer.invalidate();
#endif

#ifdef SIMULATOR
	for (int i = 0; i < 12; i++)
	{
		if (fx_controls_p[i]->update_ui(11000))
		{
			touchgfx_printf("UPDATED PARAM[%d]\n", i);
		}
	}
	swipeContainer.invalidate();

#endif
}
