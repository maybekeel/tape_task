#ifndef FILE_TAPE_CREATOR_TEST_HPP
#define FILE_TAPE_CREATOR_TEST_HPP

#include <gtest/gtest.h>

#include "file_tape_creator.hpp"

class FileTapeCreatorTest : public ::testing::Test {
   protected:
    void SetUp() override;
    std::shared_ptr<Config> config;
    std::unique_ptr<tape::FileTapeCreator> creator;
};

#endif
