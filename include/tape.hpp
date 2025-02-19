#ifndef TAPE_HPP
#define TAPE_HPP

#include <cstdint>

namespace tape {
using type = int32_t;

class ITape {
   public:
    virtual ~ITape() = default;

    virtual type read() = 0;
    virtual void write(type) = 0;
    virtual void move_forward() = 0;
    virtual void move_backward() = 0;
    virtual void rewind() = 0;
    virtual bool is_end() = 0;
    virtual bool is_begin() = 0;

   protected:
    ITape() = default;
};
}  // namespace tape

#endif
