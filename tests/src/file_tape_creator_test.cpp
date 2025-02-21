#include "file_tape_creator_test.hpp"

#include <fstream>

void FileTapeCreatorTest::SetUp() {
    config = std::make_shared<Config>("cfg/tape_task.yml");
    creator =
        std::make_unique<tape::FileTapeCreator>(config);
}

TEST_F(FileTapeCreatorTest, Create_ReturnsValidTape) {
    auto tape = creator->create();
    EXPECT_NE(tape, nullptr);
}

TEST_F(FileTapeCreatorTest, Create_CreatesUniqueFile) {
    auto tape1 = creator->create();
    std::string file1 =
        config->get_tmp_tapes().path + "0.txt";

    std::ifstream f1(file1);
    EXPECT_TRUE(f1.good())
        << "Файл " << file1 << " не был создан";
}
