#ifndef MODEL_HPP
#define MODEL_HPP

#include "main.h"
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
protected:
    ModelListener* modelListener;
    int pot1_val_adc_raw;
    int pot2_val_adc_raw;
    int pot3_val_adc_raw;
    int pot4_val_adc_raw;
    int pot5_val_adc_raw;
    int pot6_val_adc_raw;
};

#endif // MODEL_HPP
