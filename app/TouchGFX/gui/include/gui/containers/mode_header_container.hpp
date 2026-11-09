#ifndef MODE_HEADER_CONTAINER_HPP
#define MODE_HEADER_CONTAINER_HPP

#include <gui_generated/containers/mode_header_containerBase.hpp>
#include "sab_intercom.h"

class mode_header_container : public mode_header_containerBase
{
public:
    mode_header_container();
    virtual ~mode_header_container() {}

    virtual void initialize();

    // Loop boxes light up (alpha 255) when their loop bypass is active,
    // the mode box of the active preset mode lights up, all others dim to 60.
    void update(const sab_loopbypass_tun& loopbypass_un, uint8_t fx_active_mode_u8);
protected:
};

#endif // MODE_HEADER_CONTAINER_HPP
