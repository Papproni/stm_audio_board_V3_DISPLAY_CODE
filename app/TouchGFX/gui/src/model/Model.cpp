#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
extern  uint32_t adc_values_au32[6];
#endif


Model::Model() : modelListener(0), pot1_val_adc_raw(0)
{

	strcpy(this->current_fx_name,"DEFAULT");
	this->current_fx_name[19] = '\0';
}

void Model::tick()
{
//	int value = temp_value/65535.0*(-280)+139;
	#ifndef SIMULATOR
	modelListener->set_sliders_value(adc_values_au32);
#endif
}

void Model::setFXname(char* data)
{

#ifndef SIMULATOR
	stpcpy(this->current_fx_name,data);
	this->current_fx_name[20-1] = '\0';
#endif
}

void Model::getFXname(char* data)
{
#ifndef SIMULATOR
	strcpy(data,this->current_fx_name);
#endif
}


