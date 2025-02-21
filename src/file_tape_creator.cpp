#include "file_tape_creator.hpp"

#include "file_tape.hpp"

tape::FileTapeCreator::FileTapeCreator(
    const std::shared_ptr<Config>& cfg)
    : _cfg(cfg), _path(cfg->get_tmp_tapes().path) {}

auto tape::FileTapeCreator::create()
    -> std::shared_ptr<tape::ITape> {
    return std::make_shared<tape::FileTape>(
        _cfg->get_delay(),
        _path + std::to_string(_i++) + _file_format);
}
