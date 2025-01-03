#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    virtual void set_sliders_value(uint32_t* val){};
    virtual void update_screen(){};
//    virtual char* get_current_fx_name();

protected:
    Model* model;
//    uint8_t slider_value_1_u;
};

#endif // MODELLISTENER_HPP
