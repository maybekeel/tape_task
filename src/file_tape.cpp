#include "file_tape.hpp"
#include <stdexcept>
#include <thread>

tape::FileTape::FileTape(const Config::Delay& cfg, const std::string& file_name):
    _cfg(cfg),
    _tape(file_name) {
    if (!_tape) {
        throw std::runtime_error("Unable to open file " + file_name);
    }
}

int32_t tape::FileTape::read() {
    std::this_thread::sleep_for(_cfg.read_delay);
    if (is_end()) {
        std::runtime_error("Unable to read: end of file");
    }
    int32_t value;
    _prev = _tape.tellg();
    _tape >> value;
    return value;
}

void tape::FileTape::write(const int32_t value) {
    std::this_thread::sleep_for(_cfg.write_delay);
    _tape << value << '\n';
    _tape.flush();
}

void tape::FileTape::move_forward() {
    std::this_thread::sleep_for(_cfg.seek_delay);
}

void tape::FileTape::move_backward() {
    std::this_thread::sleep_for(std::chrono::milliseconds(_cfg.seek_delay));
    if (_prev != -1) {
        // Перемещаемся обратно на размер одного элемента (например, int32_t)
        _tape.seekg(_prev); // Откатываем на 4 байта (размер int32_t)
        _prev = _tape.tellg();
    } else {
        throw std::runtime_error("No previous position to move back to");
    }
}

bool tape::FileTape::is_end() {
    return _tape.eof();
}
