#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

// #include "sab_intercom.h"

#ifndef SIMULATOR
extern  uint32_t 			adc_values_au32[6];
#endif


Model::Model() : modelListener(0), pot1_val_adc_raw(0)
{
	strcpy(this->current_fx_name,"DEFAULT");
	this->current_fx_name[19] = '\0';
	#ifndef SIMULATOR
	this->intercom_pst = &sab_intercom_st;
	#endif
}

void Model::tick()
{
//	int value = temp_value/65535.0*(-280)+139;
	#ifndef SIMULATOR
	modelListener->set_sliders_value(adc_values_au32);
	
#endif
	modelListener->update_screen();
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


#ifndef SIMULATOR
void Model::read_preset_data(){
	this->intercom_pst->get_preset_data(intercom_pst);
	
}

void Model::read_loop_data(uint8_t loop_num_u8){
	this->intercom_pst->get_loop_data(intercom_pst,loop_num_u8);
}

void Model::read_fx_param(uint8_t param_slot_u8){
	this->intercom_pst->get_fx_param(intercom_pst,param_slot_u8);
}

void Model::read_info(){
	this->intercom_pst->get_info(intercom_pst);
}

void Model::read_loopbypass(){
	this->intercom_pst->get_loopbypass(intercom_pst);
}

sab_preset_num_tun  Model::get_preset_data(){
	return this->intercom_pst->preset_data_un;
}

sab_loop_num_tun   Model::get_loop_data(uint8_t loop_num_u8){
	return this->intercom_pst->loop_data[loop_num_u8];
}

sab_fx_param_tun    Model::get_fx_param(uint8_t param_slot_u8){
	return this->intercom_pst->fx_param_un[param_slot_u8];
}

sab_info_tun        Model::get_info(){
	return this->intercom_pst->info_un;
}

sab_loopbypass_tun  Model::get_loopbypass(){
	return this->intercom_pst->loopbypass_un;
}

uint8_t Model::get_num_of_implemented_fx(){
	return this->intercom_pst->num_of_implemented_effects;
}

fx_data_tst *Model::get_implemented_fx(){
	return this->intercom_pst->implemented_fx_data_ptr;
}


void Model::set_save(){
	// TODO
}

void Model::set_fx_param(uint8_t slot, uint8_t value){
	this->intercom_pst->set_fx_param(	this->intercom_pst,
										slot,value);
}

void Model::set_loopbypass(uint8_t loop, uint8_t state){
	this->intercom_pst->set_loopbypass(	this->intercom_pst,
										loop,
										state);
}

void Model::set_loop_data(sab_loop_num_tun* loop_data_pun){
	this->intercom_pst->set_loop_data(	this->intercom_pst,
										loop_data_pun,
										this->current_loop_num_u8);
}


void Model::set_current_loop_num(uint8_t loopnum){
	this->current_loop_num_u8 = loopnum;
}

void Model::set_current_fx_slot_num(uint8_t slotnum){
	this->current_fx_slot_u8 = slotnum;
}



uint8_t Model::get_current_loop_num(){
	return this->current_loop_num_u8;
}

uint8_t Model::get_current_fx_slot_num(){
	return this->current_fx_slot_u8;
}

#endif



