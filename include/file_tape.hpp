#ifndef FILE_TAPE_HPP
#define FILE_TAPE_HPP

#include <fstream>
#include "tape.hpp"
#include "config.hpp"

namespace tape {
class FileTape : public ITape {
public:
    FileTape() = delete;
    FileTape(const Config::Delay& cfg, const std::string& file_name);

    int32_t read() override final;
    void write(int32_t value) override final;
    void move_forward() override final;
    void move_backward() override final;
    bool is_end() override final;

private:
    Config::Delay _cfg;
    std::fstream _tape;
    std::streampos _prev = -1;

};
}

#endif