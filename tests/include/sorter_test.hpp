#ifndef SORTER_TEST_HPP
#define SORTER_TEST_HPP

#include <gtest/gtest.h>

#include "config.hpp"
#include "file_tape_creator.hpp"
#include "sorter.hpp"

class SorterTest : public ::testing::Test {
   protected:
    void SetUp() override;
    std::shared_ptr<Config> config;
    std::shared_ptr<tape::FileTapeCreator> creator;
    std::unique_ptr<tape::Sorter> sorter;
};

#endif
