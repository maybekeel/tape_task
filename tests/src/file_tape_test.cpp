#include "file_tape_test.hpp"

#include <fstream>

namespace {
const std::string test_file = "tests/test.txt";

Config::Delay test_delay = {std::chrono::milliseconds(10),
                            std::chrono::milliseconds(10),
                            std::chrono::milliseconds(10)};
}  // namespace

TEST(FileTapeTest, Constructor_FileExists) {
    EXPECT_NO_THROW(
        tape::FileTape tape(test_delay, test_file));
}

TEST(FileTapeTest, Constructor_EmptyFile) {
    std::string non_existent_file = "non_existent_tape.txt";
    tape::FileTape tape(test_delay, non_existent_file);
    EXPECT_ANY_THROW(tape.read());
    std::remove(non_existent_file.c_str());
}

TEST(FileTapeTest, Read_CorrectValues) {
    tape::FileTape tape(test_delay, test_file);

    EXPECT_EQ(tape.read(), 21);
    tape.move_forward();
    EXPECT_EQ(tape.read(), 534);
}

TEST(FileTapeTest, Write_And_Read) {
    tape::FileTape tape(test_delay, test_file);

    tape.write(10);
    EXPECT_EQ(tape.read(), 10);
    tape.write(21);
}

TEST(FileTapeTest, MoveBackward_And_Read) {
    tape::FileTape tape(test_delay, test_file);

    tape.move_forward();
    tape.move_forward();
    tape.move_backward();

    EXPECT_EQ(tape.read(), 534);
}

TEST(FileTapeTest, Rewind_ResetsPosition) {
    tape::FileTape tape(test_delay, test_file);

    tape.move_forward();
    tape.move_forward();
    tape.rewind();

    EXPECT_EQ(tape.read(), 21);
}

TEST(FileTapeTest, IsEnd_CorrectDetection) {
    tape::FileTape tape(test_delay, test_file);

    while (!tape.is_end()) {
        tape.move_forward();
    }

    EXPECT_TRUE(tape.is_end());
}

TEST(FileTapeTest, IsBegin_CorrectDetection) {
    tape::FileTape tape(test_delay, test_file);

    EXPECT_TRUE(tape.is_begin());
    tape.move_forward();
    EXPECT_FALSE(tape.is_begin());
}
