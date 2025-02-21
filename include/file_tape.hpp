#ifndef FILE_TAPE_HPP
#define FILE_TAPE_HPP

#include <fstream>

#include "config.hpp"
#include "tape.hpp"

namespace tape {
class FileTape : public ITape {
   public:
    FileTape() = delete;
    FileTape(const FileTape&) = delete;
    FileTape(FileTape&&) noexcept = delete;
    FileTape(const Config::Delay& cfg,
             const std::string& file_name);

    ~FileTape() = default;

    auto operator=(const FileTape&) -> FileTape& = delete;
    auto operator=(FileTape&&) -> FileTape& = delete;

    auto read() -> type override final;
    void write(type value) override final;
    void move_forward() override final;
    void move_backward() override final;
    void rewind() override final;
    auto is_end() -> bool override final;
    auto is_begin() -> bool override final;

   private:
    Config::Delay _cfg;
    std::fstream _tape;
    std::streampos _begin = -1;

    void _back();
    void _move(std::streampos pos);
};
}  // namespace tape

#endif