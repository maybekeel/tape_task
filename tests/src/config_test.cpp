#include "config_test.hpp"

#include <fstream>

#include "config.hpp"

namespace {
const std::string cfg_name = "cfg/tape_task.yml";
const std::string bad_cfg_name = "bad_config.yaml";
}  // namespace

TEST(ConfigTest, Constructor_ValidConfig) {
    Config config(cfg_name);

    auto delay = config.get_delay();
    EXPECT_EQ(delay.read_delay.count(), 100);
    EXPECT_EQ(delay.write_delay.count(), 200);
    EXPECT_EQ(delay.seek_delay.count(), 50);

    auto tmp_tapes = config.get_tmp_tapes();
    EXPECT_FALSE(tmp_tapes.path.empty());
}

TEST(ConfigTest, Constructor_EmptyPath) {
    EXPECT_THROW(Config(""), std::invalid_argument);
}

TEST(ConfigTest, Constructor_InvalidFile) {
    EXPECT_THROW(Config("non_existent.yaml"),
                 std::runtime_error);
}

TEST(ConfigTest, Constructor_InvalidTmpTapesPath) {
    std::ofstream config_file(bad_cfg_name);
    config_file << "delay:\n  read_delay: 100\n  "
                   "write_delay: 200\n  seek_delay: 50\n";
    config_file.close();

    EXPECT_THROW({ Config config(bad_cfg_name); },
                 std::runtime_error);
}

TEST(ConfigTest, GetTmpTapes_ValidConfig) {
    Config config(cfg_name);
    auto tmp_tapes = config.get_tmp_tapes();

    EXPECT_FALSE(tmp_tapes.path.empty());
}
