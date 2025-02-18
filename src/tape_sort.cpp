#include "tape_sort.hpp"
#include <algorithm>
#include <iostream>
TapeSorter::TapeSorter(std::shared_ptr<tape::ITape> in, std::shared_ptr<tape::ITape> out):
    _in(in),
    _out(out) {}

void TapeSorter::sort() {
    while (!_in->is_end()) {
        _out->write(_in->read());
        _out->move_forward();
        _in->move_forward();
    }
    _in->move_backward();
    _in->move_backward();
    std::cout << _in->read() << std::endl;
    std::cout << _in->read() << std::endl;
    // _in->move_backward();
    // std::cout << _in->read() << std::endl;
    // _in->move_backward();
    // std::cout << _in->read() << std::endl;
    // _in->move_backward();

}
