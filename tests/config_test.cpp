#include "config_test.hpp"

#include <fstream>

#include "config.hpp"
namespace {
std::string cfg_name = "cfg/tape_task.yml";
}

TEST(ConfigTest, Constructor_ValidConfig) {
    Config config(cfg_name);
    auto delay = config.get_delay();
    EXPECT_EQ(delay.read_delay.count(), 100);
    EXPECT_EQ(delay.write_delay.count(), 200);
    EXPECT_EQ(delay.seek_delay.count(), 50);
}

TEST(ConfigTest, Constructor_EmptyPath) {
    EXPECT_THROW(Config(""), std::invalid_argument);
}

TEST(ConfigTest, Constructor_InvalidFile) {
    EXPECT_THROW(Config("non_existent.yaml"),
                 std::runtime_error);
}

TEST(ConfigTest, Constructor_MissingFields) {
    std::ofstream config_file("bad_config.yaml");
    config_file << "delay:\n  read_delay: 100\n";
    config_file.close();

    EXPECT_THROW(Config("bad_config.yaml"), std::exception);
    std::remove("bad_config.yaml");
}