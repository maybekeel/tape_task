#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <chrono>

class Config {
private:
    using ms = std::chrono::milliseconds;
public:
    explicit Config(const std::string& cfg_path);
    struct Delay {
        ms read_delay;
        ms write_delay;
        ms seek_delay;
    };

    const Delay& get_delay() const noexcept;

private:
    Delay _delay;
};

#endif
