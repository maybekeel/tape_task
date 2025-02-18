#include <yaml-cpp/yaml.h>
#include <chrono>
#include <stdexcept>
#include "config.hpp"

Config::Config(const std::string& cfg_path) {
    if (cfg_path.empty()) {
        throw std::invalid_argument("Bad config file path");
    }
    auto cfg = YAML::LoadFile(cfg_path);
    _delay = {
        static_cast<ms>(cfg["delay"]["read_delay"].as<int>()),
        static_cast<ms>(cfg["delay"]["write_delay"].as<int>()),
        static_cast<ms>(cfg["delay"]["seek_delay"].as<int>()),
    };
}

auto Config::Config::get_delay() const noexcept -> const Delay& {
    return _delay;
}
