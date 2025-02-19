#include "file_tape_create.hpp"

#include "file_tape.hpp"

FileTapeCreator::FileTapeCreator(const Config::Delay& cfg,
                                 const std::string& path)
    : _cfg(cfg), _path(path) {}

std::shared_ptr<tape::ITape> FileTapeCreator::create() {
    return std::make_shared<tape::FileTape>(
        _cfg, _path + std::to_string(_i++) + ".txt");
}
