#ifndef TAPE_SORT_HPP
#define TAPE_SORT_HPP

#include "tape.hpp"
#include <memory>

class TapeSorter {
public:
    TapeSorter(std::shared_ptr<tape::ITape> in, std::shared_ptr<tape::ITape> out);
    void sort();
private:
    std::shared_ptr<tape::ITape> _in;
    std::shared_ptr<tape::ITape> _out;
};

#endif
