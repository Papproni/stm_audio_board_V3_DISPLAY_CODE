#ifndef MODEL_HPP
#define MODEL_HPP

#ifndef SIMULATOR
#include "main.h"
#include "sab_intercom.h"

extern  sab_intercom_tst 	sab_intercom_st;

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
    
    // intercom data SETTERS (does comm too)
    void               set_save();
    void               set_fx_param(uint8_t slot, uint8_t value);
    void               set_loopbypass(uint8_t loop, uint8_t state);
    #endif
    char current_fx_name[20];
protected:
    ModelListener* modelListener;
    #ifndef SIMULATOR
    sab_intercom_tst* intercom_pst;
    #endif
    int pot1_val_adc_raw;
    int pot2_val_adc_raw;
    int pot3_val_adc_raw;
    int pot4_val_adc_raw;
    int pot5_val_adc_raw;
    int pot6_val_adc_raw;
};

#endif // MODEL_HPP
