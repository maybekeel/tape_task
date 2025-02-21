#include "config.hpp"

#include <yaml-cpp/yaml.h>

#include <chrono>
#include <stdexcept>

Config::Config(const std::string& cfg_path) {
    if (cfg_path.empty()) {
        throw std::invalid_argument("Bad config file path");
    }
    auto cfg = YAML::LoadFile(cfg_path);
    _delay = {
        static_cast<ms>(
            cfg["delay"]["read_delay"].as<int>()),
        static_cast<ms>(
            cfg["delay"]["write_delay"].as<int>()),
        static_cast<ms>(
            cfg["delay"]["seek_delay"].as<int>()),
    };
    _tmp_tapes = {
        cfg["tmp_tapes"]["path"].as<std::string>()};
}

auto Config::Config::get_delay() const noexcept
    -> const Delay& {
    return _delay;
}

auto Config::Config::get_tmp_tapes() const noexcept
    -> const TmpTapes& {
    return _tmp_tapes;
}
