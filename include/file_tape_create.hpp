#ifndef FILE_TAPE_CREATE_HPP
#define FILE_TAPE_CREATE_HPP

#include <cstddef>
#include <memory>

#include "config.hpp"
#include "tape.hpp"
#include "tape_create.hpp"

class FileTapeCreator : public ITapeCreator {
   public:
    FileTapeCreator(const Config::Delay& cfg,
                    const std::string& path);
    std::shared_ptr<tape::ITape> create() override final;

   private:
    Config::Delay _cfg;
    std::string _path;
    size_t _i = 0;
};

#endif
