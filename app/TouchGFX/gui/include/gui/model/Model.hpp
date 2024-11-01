#ifndef MODEL_HPP
#define MODEL_HPP

#ifndef SIMULATOR
#include "main.h"
#include "sab_intercom.h"

extern  sab_intercom_tst 	sab_intercom_st;

extern  uint32_t 			adc_values_au32[6];
#endif

// #include "../../../../Core/Inc/sab_intercom.h"

#include <stdint.h>
#include "string.h"
class ModelListener;


class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void setFXname(char* name);
    void getFXname(char* data);

#ifndef SIMULATOR
    // Hardware comm triggers
    void                read_preset_data();
    void                read_loop_data(uint8_t loop_num_u8);
    void                read_fx_param(uint8_t param_slot_u8);
    void                read_info();
    void                read_loopbypass();

    // intercom data GETTERS (NO COMM)
    sab_preset_num_tun  get_preset_data();
    sab_loop_num_tun    get_loop_data(uint8_t loop_num_u8);
    sab_fx_param_tun    get_fx_param(uint8_t param_slot_u8);
    sab_info_tun        get_info();
    sab_loopbypass_tun  get_loopbypass();
    uint8_t             get_num_of_implemented_fx();
    fx_data_tst*        get_implemented_fx();
    
    // intercom data SETTERS (does comm too)
    void               set_save();
    void               set_fx_param(uint8_t slot, uint8_t value);
    void               set_loopbypass(uint8_t loop, uint8_t state);
    void               set_loop_data(sab_loop_num_tun* loop_data_pun);
    
    void set_current_loop_num(uint8_t loopnum);
    void set_current_fx_slot_num(uint8_t slotnum);

    uint8_t get_current_loop_num();
    uint8_t get_current_fx_slot_num();

    uint32_t* get_adc_value_ptr();
#endif

    char        current_fx_name[20];
    uint32_t*    pot_ctrl_adc_pau32;
protected:
    ModelListener* modelListener;
    #ifndef SIMULATOR
    sab_intercom_tst* intercom_pst;
    #endif

    uint8_t current_loop_num_u8;
    uint8_t current_fx_slot_u8;

};

#endif // MODEL_HPP
