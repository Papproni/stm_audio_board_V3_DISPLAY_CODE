/*
 * sab_intercom.c
 *
 *  Created on: Oct 11, 2024
 *      Author: pappr
 */

#include "sab_intercom.h"

// ----------------------------------GETTERS-------------------------------------------------
static void get_preset_data (struct sab_intercom_st* self){
    HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
                        SAB_I2C_REG_PRESETNUM, I2C_MEMADD_SIZE_8BIT,
                        &self->preset_data_un.all_u32, SAB_I2C_REG_PRESETNUM_LEN,
                        1000);
}
static void get_loop_data (struct sab_intercom_st* self, uint8_t loop_num_u8){
	HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_LOOP1FX+loop_num_u8-1,
						I2C_MEMADD_SIZE_8BIT,
						self->loop_data->all_pau8, SAB_I2C_REG_LOOPFX_LEN,
						1000);
}
static void get_fx_param(struct sab_intercom_st* self, uint8_t param_slot_u8){
	HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_FXPARAM1+param_slot_u8-1,
						I2C_MEMADD_SIZE_8BIT,
						&self->fx_param_un[param_slot_u8-1].all_au8, SAB_I2C_REG_FXPARAM_LEN,
						1000);
}

static void get_info (struct sab_intercom_st* self){
	HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_INFO,
						I2C_MEMADD_SIZE_8BIT,
						&self->info_un.all_u8, SAB_I2C_REG_INFO_LEN,
						1000);
}
static void get_loopbypass (struct sab_intercom_st* self){
	HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_LOOPBYPASSSTATE,
						I2C_MEMADD_SIZE_8BIT,
						&self->loopbypass_un.all_u8, SAB_I2C_REG_LOOPBYPASSSTATE_LEN,
						1000);
}

// ----------------------------------SETTERS-------------------------------------------------
static void set_fx_param (struct sab_intercom_st* self, uint8_t param_slot_u8, uint8_t new_value_u8){
	self->fx_param_un[param_slot_u8-1].value_u8 = new_value_u8;

	HAL_I2C_Mem_Write(self->i2c_h,self->slave_addr_u8,
			SAB_I2C_REG_FXPARAM1+param_slot_u8-1,
			I2C_MEMADD_SIZE_8BIT,
			&self->fx_param_un[param_slot_u8-1], SAB_I2C_REG_FXPARAM_LEN, 1000);
}

static void set_loopbypass (struct sab_intercom_st* self){
	HAL_I2C_Mem_Write(self->i2c_h,self->slave_addr_u8,
				SAB_I2C_REG_LOOPBYPASSSTATE,
				I2C_MEMADD_SIZE_8BIT,
				&self->loopbypass_un.all_u8, SAB_I2C_REG_LOOPBYPASSSTATE_LEN, 1000);
}

// ----------------------------------INIT-------------------------------------------------
void init_intercom(struct sab_intercom_st* self, uint8_t slave_address_u8,I2C_HandleTypeDef *i2c_h){
    self->slave_addr_u8 = slave_address_u8<<1;
    self->i2c_h = i2c_h;
    // GETTER function pointers
    self->get_preset_data   = get_preset_data;
    self->get_loop_data     = get_loop_data  ;
    self->get_fx_param		= get_fx_param   ;
    self->get_info          = get_info       ;
    self->get_loopbypass    = get_loopbypass ;

    // SETTER function pointers
    self->set_fx_param      = set_fx_param;
    self->set_loopbypass	= set_loopbypass;
}

void testing_data(struct sab_intercom_st* self){
    
    strcpy(self->fx_param_un[0].name,"TIME");
    self->fx_param_un[0].type_en = 5;
    self->fx_param_un[0].value_u8 = 69;
}
