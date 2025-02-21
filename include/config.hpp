#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <chrono>
#include <string>

class Config {
   private:
    using ms = std::chrono::milliseconds;

   public:
    Config() = delete;
    Config(const Config&) = default;
    Config(Config&&) noexcept = default;
    explicit Config(const std::string& cfg_path);
    ~Config() = default;

    auto operator=(const Config&) -> Config& = default;
    auto operator=(Config&&) noexcept -> Config& = default;

    struct Delay {
        ms read_delay;
        ms write_delay;
        ms seek_delay;
    };
    struct TmpTapes {
        std::string path;
    };

    const Delay& get_delay() const noexcept;
    const TmpTapes& get_tmp_tapes() const noexcept;

   private:
    Delay _delay;
    TmpTapes _tmp_tapes;
};

#endif
