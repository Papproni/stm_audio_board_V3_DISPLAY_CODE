#ifndef MODE_HEADER_CONTAINER_HPP
#define MODE_HEADER_CONTAINER_HPP

#include <gui_generated/containers/mode_header_containerBase.hpp>

class mode_header_container : public mode_header_containerBase
{
public:
    mode_header_container();
    virtual ~mode_header_container() {}

    virtual void initialize();
protected:
};

#endif // MODE_HEADER_CONTAINER_HPP
