#include "sorter_test.hpp"
#include "file_tape.hpp"

void SorterTest::SetUp() {
    config = std::make_shared<Config>("cfg/tape_task.yml");
    creator =
        std::make_shared<tape::FileTapeCreator>(config);
    sorter = std::make_unique<tape::Sorter>(creator);
}

TEST_F(SorterTest, Sort_SmallArray) {
    auto input = creator->create();
    auto output = creator->create();

    std::vector<tape::type> values = {5, 3, 8, 1, 4};
    std::for_each(values.begin(), values.end(),
                  [&](const tape::type val) {
                      input->write(val);
                      input->move_forward();
                  });
    input->rewind();
    sorter->sort(input, output, values.size(), 1024);
    output->rewind();
    std::vector<tape::type> sorted_values;
    while (!output->is_end()) {
        sorted_values.emplace_back(output->read());
        output->move_forward();
    }
    EXPECT_EQ(sorted_values,
              (std::vector<tape::type>{1, 3, 4, 5, 8}));
}

TEST_F(SorterTest, Sort_EmptyInput) {
    auto input = creator->create();
    auto output = creator->create();

    sorter->sort(input, output, 0, 1024);

    output->rewind();
    EXPECT_TRUE(output->is_begin());
}

TEST_F(SorterTest, Sort_LargeData) {
    auto input = std::make_shared<tape::FileTape>(config->get_delay(), "tests/large.txt");
    auto output = creator->create();
    sorter->sort(input, output, 1000, 2048);
    output->rewind();
    for (tape::type i = 1; i <= 1000; ++i) {
        EXPECT_EQ(output->read(), i);
        output->move_forward();
    }
}
