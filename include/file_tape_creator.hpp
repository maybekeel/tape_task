#ifndef FILE_TAPE_CREATE_HPP
#define FILE_TAPE_CREATE_HPP

#include <cstddef>
#include <memory>

#include "config.hpp"
#include "creator.hpp"
#include "tape.hpp"

namespace tape {
class FileTapeCreator : public ICreator {
   private:
    using Self = FileTapeCreator;

   public:
    FileTapeCreator() = delete;
    FileTapeCreator(const Self&) = default;
    FileTapeCreator(Self&&) noexcept = default;
    FileTapeCreator(const std::shared_ptr<Config>& cfg);
    ~FileTapeCreator() = default;

    auto operator=(const Self&) -> Self& = default;
    auto operator=(Self&&) noexcept -> Self& = default;

    auto create()
        -> std::shared_ptr<tape::ITape> override final;

   private:
    const std::shared_ptr<Config> _cfg;
    const std::string _path;
    const std::string _file_format{".txt"};
    size_t _i = 0;
};
}  // namespace tape

#endif
