#include "file_tape.hpp"

#include <ios>
#include <stdexcept>
#include <thread>

tape::FileTape::FileTape(const Config::Delay& cfg,
                         const std::string& file_name)
    : _cfg(cfg),
      _tape(file_name, std::ios::in | std::ios::out) {
    if (!_tape) {
        std::ofstream(file_name).close();
        _tape.open(file_name, std::ios::in | std::ios::out);
    }
    if (!_tape) {
        throw std::runtime_error("Unable to open file " +
                                 file_name);
    }
    _begin = _tape.tellg();
}

auto tape::FileTape::read() -> type {
    std::this_thread::sleep_for(_cfg.read_delay);
    if (is_end()) {
        std::runtime_error("Unable to read: end of file");
    }
    auto pos = _tape.tellg();
    type value;
    _tape >> value;
    if (_tape.fail()) {
        _tape.clear();
        throw std::runtime_error(
            "Unable to read: invalid file");
    }
    _tape.seekg(pos);
    return value;
}

void tape::FileTape::write(const type value) {
    std::this_thread::sleep_for(_cfg.write_delay);
    _tape.clear();
    auto pos = _tape.tellg();
    if (!is_begin()) {
        _tape << '\n';
    }
    _tape << value;
    _tape.flush();
    _tape.seekg(pos);
}

void tape::FileTape::move_forward() {
    if (is_end()) {
        return;
    }
    std::this_thread::sleep_for(_cfg.seek_delay);
    type value;
    _tape >> value;
}

void tape::FileTape::move_backward() {
    if (is_begin()) {
        return;
    }
    std::this_thread::sleep_for(
        std::chrono::milliseconds(_cfg.seek_delay));
    _tape.clear();
    if (_tape.peek() == '\n') {
        _back();
    }
    while (!is_begin() &&_tape.peek() != '\n') {
        _back();
    }
}

void tape::FileTape::rewind() {
    std::this_thread::sleep_for(_cfg.seek_delay);
    _tape.clear();
    _tape.seekg(_begin, std::ios::beg);
}

auto tape::FileTape::is_end() -> bool {
    if (_tape.eof()) {
        return true;
    }
    auto pos = _tape.tellg();
    type value;
    _tape >> value;
    if (_tape.fail()) {
        _tape.clear();
        _tape.seekg(pos);
        return true;
    }
    _tape.seekg(pos);
    return false;
}

auto tape::FileTape::is_begin() -> bool {
    return _tape.tellg() == _begin;
}

void tape::FileTape::_back() {
    _tape.seekg(-1, std::ios_base::cur);
    if (_tape.fail()) {
        _tape.clear();
    }
}
