#ifndef TAPE_CREATE_HPP
#define TAPE_CREATE_HPP

#include <memory>

#include "tape.hpp"

class ITapeCreator {
   public:
    ~ITapeCreator() = default;
    virtual std::shared_ptr<tape::ITape> create() = 0;

   protected:
    ITapeCreator() = default;
};

#endif
