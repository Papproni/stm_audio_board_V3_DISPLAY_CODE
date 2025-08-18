#ifndef MODE_PRESET_DISPLAY_CONTAINER_HPP
#define MODE_PRESET_DISPLAY_CONTAINER_HPP

#include <gui_generated/containers/mode_preset_display_containerBase.hpp>

class mode_preset_display_container : public mode_preset_display_containerBase
{
public:
    mode_preset_display_container();
    virtual ~mode_preset_display_container() {}

    virtual void initialize();
protected:
};

#endif // MODE_PRESET_DISPLAY_CONTAINER_HPP
