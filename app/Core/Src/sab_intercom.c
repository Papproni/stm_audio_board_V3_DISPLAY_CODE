/*
 * sab_intercom.c
 *
 *  Created on: Oct 11, 2024
 *      Author: pappr
 */

#include "sab_intercom.h"

// ----------------------------------I2C BUS HEALTH-------------------------------------------------
// Every I2C transaction below runs on the GUI thread. If the DSP slave stops answering
// (crash, brownout, stuck bus), a blocking HAL_I2C_Mem_Read/Write would stall the whole
// GUI for the full timeout on every call - with per-frame polling that freezes the UI
// completely (buttons become unpressable). To keep the GUI alive:
//   1) the per-transaction timeout is short (SAB_I2C_TIMEOUT_MS), and
//   2) after SAB_I2C_FAIL_LIMIT consecutive failures all transactions are skipped for
//      SAB_I2C_BACKOFF_MS, retrying periodically instead of hammering a dead bus.
#define SAB_I2C_TIMEOUT_MS     300U
#define SAB_I2C_FAIL_LIMIT     3U
#define SAB_I2C_BACKOFF_MS     3000U

static uint8_t  sab_i2c_fail_count_u8 = 0;
static uint32_t sab_i2c_backoff_until_u32 = 0;

/// @brief 1 if a transaction may be attempted now, 0 while in backoff (keep stale data).
static int sab_i2c_bus_ready(void){
	return (HAL_GetTick() >= sab_i2c_backoff_until_u32);
}

/// @brief Feed the result of a transaction into the backoff logic.
static void sab_i2c_note_result(int ok){
	if(ok){
		sab_i2c_fail_count_u8 = 0;
		sab_i2c_backoff_until_u32 = 0;
	}else{
		if(++sab_i2c_fail_count_u8 >= SAB_I2C_FAIL_LIMIT){
			sab_i2c_backoff_until_u32 = HAL_GetTick() + SAB_I2C_BACKOFF_MS;
		}
	}
}

// ----------------------------------GETTERS-------------------------------------------------
static void get_preset_data (struct sab_intercom_st* self){
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
                        SAB_I2C_REG_PRESETNUM, I2C_MEMADD_SIZE_8BIT,
						(uint8_t*)&self->preset_data_un.all_u32, SAB_I2C_REG_PRESETNUM_LEN,
                        SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}

/*
1 = LOOP1
2 = LOOP2
3 = LOOP3
4 = LOOP4
*/
static void get_loop_data (struct sab_intercom_st* self, uint8_t loop_num_u8){
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_LOOP1FX+loop_num_u8-1,
						I2C_MEMADD_SIZE_8BIT,
						self->loop_data[loop_num_u8-1].all_pau8, sizeof(sab_loop_num_tun),
						SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}


static void get_fx_param(struct sab_intercom_st* self, uint8_t param_slot_u8){
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_FXPARAM1+param_slot_u8-1,
						I2C_MEMADD_SIZE_8BIT,
						(uint8_t*)&self->fx_param_un[param_slot_u8-1].all_au8, SAB_I2C_REG_FXPARAM_LEN,
						SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}

static void get_info (struct sab_intercom_st* self){
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_INFO,
						I2C_MEMADD_SIZE_8BIT,
						(uint8_t*)&self->info_un.all_u8, SAB_I2C_REG_INFO_LEN,
						SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}
static void get_loopbypass (struct sab_intercom_st* self){
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_LOOPBYPASSSTATE,
						I2C_MEMADD_SIZE_8BIT,
						(uint8_t*)&self->loopbypass_un.all_u8, SAB_I2C_REG_LOOPBYPASSSTATE_LEN,
						SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}

static void get_num_of_implemented_effects  (struct sab_intercom_st* self){
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_NUM_OF_IMPLEMENTED_EFFECTS,
						I2C_MEMADD_SIZE_8BIT,
						(uint8_t*)&self->num_of_implemented_effects, 1,
						SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}

static void get_implemented_effects  (struct sab_intercom_st* self){


	// Boot path: wait until the DSP reports how many effects it has. The per-call bus
	// backoff makes get_num_of_implemented_effects() return instantly while in backoff,
	// so pace the retry with a delay instead of spinning the CPU.
	while(!self->num_of_implemented_effects){
		get_num_of_implemented_effects(self);
		HAL_Delay(50);
	}
	
	self->implemented_fx_data_ptr = malloc(sizeof(fx_data_tst)*self->num_of_implemented_effects);
	if(NULL == self->implemented_fx_data_ptr){
		return;
	}

	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Read(self->i2c_h, self->slave_addr_u8,
						SAB_I2C_REG_IMPLEMENTED_EFFECTS,
						I2C_MEMADD_SIZE_8BIT,
						(uint8_t*)self->implemented_fx_data_ptr, sizeof(fx_data_tst)*self->num_of_implemented_effects,
						SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}


// ----------------------------------SETTERS-------------------------------------------------
static void set_fx_param (struct sab_intercom_st* self, uint8_t param_slot_u8, uint8_t new_value_u8){
	self->fx_param_un[param_slot_u8-1].value_u8 = new_value_u8;

	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Write(self->i2c_h,self->slave_addr_u8,
			SAB_I2C_REG_FXPARAM1+param_slot_u8-1,
			I2C_MEMADD_SIZE_8BIT,
			(uint8_t*)&self->fx_param_un[param_slot_u8-1], SAB_I2C_REG_FXPARAM_LEN, SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}

static void set_loopbypass (struct sab_intercom_st* self,uint8_t loop, uint8_t state){
	self->loopbypass_un.all_u8[loop] = state;
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Write(self->i2c_h,self->slave_addr_u8,
						SAB_I2C_REG_LOOPBYPASSSTATE,
						I2C_MEMADD_SIZE_8BIT,
						(uint8_t*)&self->loopbypass_un.all_u8, SAB_I2C_REG_LOOPBYPASSSTATE_LEN, SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}
static void set_save (struct sab_intercom_st* self){
	
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Write(self->i2c_h,self->slave_addr_u8,
						SAB_I2C_REG_SAVEPRESET,
						I2C_MEMADD_SIZE_8BIT,
						(uint8_t*)&self->save_un, sizeof(sab_save_tun), SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
	HAL_Delay(500);
}

/*
	loop_num:
		1 = LOOP1
		2 = LOOP2
		3 = LOOP3
		4 = LOOP4
*/
static void set_loop_data  (struct sab_intercom_st* self, sab_loop_num_tun* loop_data_pun, uint8_t loop_num){
	memcpy(self->loop_data[loop_num-1].all_pau8,loop_data_pun,sizeof(sab_loop_num_tun));
	
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Write(self->i2c_h,self->slave_addr_u8,
						SAB_I2C_REG_LOOP1FX+loop_num-1,
						I2C_MEMADD_SIZE_8BIT,
						self->loop_data[loop_num-1].all_pau8, sizeof(sab_loop_num_tun), SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}

static void set_current_fx_in_edit (struct sab_intercom_st* self,uint8_t fx_slot_u8){
	self->current_fx_in_edit = fx_slot_u8;
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Write(self->i2c_h,self->slave_addr_u8,
						SAB_I2c_REG_CURRENT_FX,
						I2C_MEMADD_SIZE_8BIT,
						&self->current_fx_in_edit, sizeof(uint8_t), SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}

static void set_dsp_fw_update_flg(struct sab_intercom_st* self){
	self->dsp_fw_update_flg = 1;
	if(!sab_i2c_bus_ready()){ return; }
	HAL_StatusTypeDef st = HAL_I2C_Mem_Write(self->i2c_h,self->slave_addr_u8,
						SAB_I2C_REG_DSP_FW_UPDATE,
						I2C_MEMADD_SIZE_8BIT,
						&self->dsp_fw_update_flg, sizeof(uint8_t), SAB_I2C_TIMEOUT_MS);
	sab_i2c_note_result(st == HAL_OK);
}



/// @brief Saves data received from master (display)
/// @param self
/// @param buffer_pu8
/// @param size_u8
void sab_intercom_process_i2c_data(struct sab_intercom_st* self, uint8_t*buffer_pu8, uint8_t size_u8){
	memcpy((uint8_t*)self->get_reg_data_ptr(self),buffer_pu8,size_u8);
}

/// @brief This function returns the data pointer which is adressed by the "register_addr_u8"
/// @param self
/// @return
uint32_t sab_intercom_get_reg_data_ptr(struct sab_intercom_st* self){
	switch (self->register_addr_u8)
	{
		case SAB_I2C_REG_PRESETNUM:
			return (uint32_t)&self->preset_data_un;  // Returns pointer to the preset data union

		case SAB_I2C_REG_LOOP1FX:
			return (uint32_t)&self->loop_data[0];    // Returns pointer to the first loop

		case SAB_I2C_REG_LOOP2FX:
			return (uint32_t)&self->loop_data[1];    // Returns pointer to the second loop

		case SAB_I2C_REG_LOOP3FX:
			return (uint32_t)&self->loop_data[2];    // Returns pointer to the third loop

		case SAB_I2C_REG_LOOP4FX:
			return (uint32_t)&self->loop_data[3];    // Returns pointer to the fourth loop

		case SAB_I2C_REG_FXPARAM1:
			return (uint32_t)&self->fx_param_un[0];  // Returns pointer to the first FX parameter

		case SAB_I2C_REG_FXPARAM2:
			return (uint32_t)&self->fx_param_un[1];  // Returns pointer to the second FX parameter

		case SAB_I2C_REG_FXPARAM3:
			return (uint32_t)&self->fx_param_un[2];  // Returns pointer to the third FX parameter

		case SAB_I2C_REG_FXPARAM4:
			return (uint32_t)&self->fx_param_un[3];  // Returns pointer to the fourth FX parameter

		case SAB_I2C_REG_FXPARAM5:
			return (uint32_t)&self->fx_param_un[4];  // Returns pointer to the fifth FX parameter

		case SAB_I2C_REG_FXPARAM6:
			return (uint32_t)&self->fx_param_un[5];  // Returns pointer to the sixth FX parameter

		case SAB_I2C_REG_FXPARAM7:
			return (uint32_t)&self->fx_param_un[6];  // Returns pointer to the seventh FX parameter

		case SAB_I2C_REG_FXPARAM8:
			return (uint32_t)&self->fx_param_un[7];  // Returns pointer to the eighth FX parameter

		case SAB_I2C_REG_FXPARAM9:
			return (uint32_t)&self->fx_param_un[8];  // Returns pointer to the ninth FX parameter

		case SAB_I2C_REG_FXPARAM10:
			return (uint32_t)&self->fx_param_un[9];  // Returns pointer to the tenth FX parameter

		case SAB_I2C_REG_FXPARAM11:
			return (uint32_t)&self->fx_param_un[10]; // Returns pointer to the eleventh FX parameter

		case SAB_I2C_REG_FXPARAM12:
			return (uint32_t)&self->fx_param_un[11]; // Returns pointer to the twelfth FX parameter

		case SAB_I2C_REG_INFO:
			return (uint32_t)&self->info_un;          // Returns pointer to the info union

		case SAB_I2C_REG_SAVEPRESET:
			return (uint32_t)&self->save_un;          // Returns pointer to the save union

		case SAB_I2C_REG_LOOPBYPASSSTATE:
			return (uint32_t)&self->loopbypass_un;    // Returns pointer to the loop bypass union

		case SAB_I2C_REG_NUM_OF_IMPLEMENTED_EFFECTS:
			return (uint32_t)&self->num_of_implemented_effects;
		
		case SAB_I2C_REG_IMPLEMENTED_EFFECTS:
			return (uint32_t)self->implemented_fx_data_ptr;
		
		case SAB_I2c_REG_CURRENT_FX:
			return (uint32_t)&self->current_fx_in_edit;
		
		case SAB_I2C_REG_DSP_FW_UPDATE:
			return (uint32_t)&self->dsp_fw_update_flg;

		default:
			return 0;  // Return NULL if the register enum is out of bounds
    }
}

uint16_t sab_intercom_get_reg_data_size(struct sab_intercom_st* self){
	switch (self->register_addr_u8)
	{
		case SAB_I2C_REG_PRESETNUM:
			return sizeof(sab_preset_num_tun);  // Returns pointer to the preset data union

		case SAB_I2C_REG_LOOP1FX:
		case SAB_I2C_REG_LOOP2FX:
		case SAB_I2C_REG_LOOP3FX:
		case SAB_I2C_REG_LOOP4FX:
			return sizeof(sab_loop_num_tun);    // Returns pointer to the fourth loop

		case SAB_I2C_REG_FXPARAM1:
		case SAB_I2C_REG_FXPARAM2:
		case SAB_I2C_REG_FXPARAM3:
		case SAB_I2C_REG_FXPARAM4:
		case SAB_I2C_REG_FXPARAM5:
		case SAB_I2C_REG_FXPARAM6:
		case SAB_I2C_REG_FXPARAM7:
		case SAB_I2C_REG_FXPARAM8:
		case SAB_I2C_REG_FXPARAM9:
		case SAB_I2C_REG_FXPARAM10:
		case SAB_I2C_REG_FXPARAM11:
		case SAB_I2C_REG_FXPARAM12:
			return sizeof(sab_fx_param_tun); // Returns pointer to the twelfth FX parameter

		case SAB_I2C_REG_INFO:
			return sizeof(sab_info_tun);          // Returns pointer to the info union

		case SAB_I2C_REG_SAVEPRESET:
			return sizeof(sab_save_tun);           // Returns pointer to the save union

		case SAB_I2C_REG_LOOPBYPASSSTATE:
			return sizeof(sab_loopbypass_tun);          // Returns pointer to the loop bypass union
		
		case SAB_I2C_REG_NUM_OF_IMPLEMENTED_EFFECTS:
			return sizeof(uint8_t);          // Returns pointer to the loop bypass union
		
		case SAB_I2C_REG_IMPLEMENTED_EFFECTS:
			return sizeof(fx_data_tst)*self->num_of_implemented_effects;          // Returns pointer to the loop bypass union
		
		case SAB_I2c_REG_CURRENT_FX:
			return sizeof(uint8_t);
		
		case SAB_I2C_REG_DSP_FW_UPDATE:
			return sizeof(uint8_t);

		default:
			return 0;  // Return NULL if the register enum is out of bounds
    }
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

	self->get_implemented_effects			= get_implemented_effects;
	self->num_of_implemented_effects 		= 0;
	self->implemented_fx_data_ptr			= NULL;

    // SETTER function pointers
    self->set_fx_param      = set_fx_param;
    self->set_loopbypass	= set_loopbypass;
	self->set_loop_data 	= set_loop_data;
	self->set_current_fx_in_edit = set_current_fx_in_edit;
	self->set_save				=set_save;
	self->set_dsp_fw_update_flg = set_dsp_fw_update_flg;

	self->process_rx_buffer = sab_intercom_process_i2c_data;
	self->get_reg_data_ptr = sab_intercom_get_reg_data_ptr;
	self->get_reg_data_len = sab_intercom_get_reg_data_size;


	self->save_un.save_command 	= 1;
	self->dsp_fw_update_flg 	= 0;
}
