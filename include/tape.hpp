#ifndef TAPE_HPP
#define TAPE_HPP

#include <cstdint>

namespace tape {
class ITape {
public:
    virtual ~ITape() = default;

    virtual int32_t read() = 0;
    virtual void write(int32_t) = 0;
    virtual void move_forward() = 0;
    virtual void move_backward() = 0;
    virtual bool is_end() = 0;

protected:
    ITape() = default;
};
}

#endif
