#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0), pot1_val_adc_raw(0)
{
}

void Model::tick()
{

	this->pot1_val_adc_raw++;
	if(this->pot1_val_adc_raw>140){
		this->pot1_val_adc_raw=-120;
	}
	modelListener->set_slider1_value(this->pot1_val_adc_raw);
}
