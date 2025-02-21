#ifndef CREATOR_HPP
#define CREATOR_HPP

#include <memory>

#include "tape.hpp"

namespace tape {
class ICreator {
   public:
    ~ICreator() = default;
    virtual auto create()
        -> std::shared_ptr<tape::ITape> = 0;

   protected:
    ICreator() = default;
};
}  // namespace tape
#endif
