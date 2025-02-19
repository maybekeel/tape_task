#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>

#include "config.hpp"
#include "file_tape.hpp"
#include "file_tape_create.hpp"
#include "include/file_tape.hpp"
#include "include/file_tape_create.hpp"
#include "include/tape_sort.hpp"
#include "tape.hpp"
#include "tape_create.hpp"
#include "tape_sort.hpp"

int main(int argc, char** argv) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string in_name, out_name;
    size_t n = 0, m = 0;
    if (argc > 4) {
        in_name = argv[1];
        out_name = argv[2];
        n = std::stoul(argv[3]);
        m = std::stoul(argv[4]);
    } else {
        std::cerr << "Bad args\n";
        return 1;
    }
    Config cfg("cfg/tape_task.yml");

    auto in = std::make_shared<tape::FileTape>(
        cfg.get_delay(), in_name);
    auto out = std::make_shared<tape::FileTape>(
        cfg.get_delay(), out_name);

    auto creator = std::make_shared<FileTapeCreator>(
        cfg.get_delay(), "/home/ivlicheva/tape_task/");
    // auto tmp = creator->create();
    TapeSorter sorter(creator);
    // sorter._mergesort(first, second);
    sorter.sort(in, out, m);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<
        std::chrono::milliseconds>(end - start);
    std::cout << "Время выполнения: " << duration.count()
              << " мс" << std::endl;
    return 0;
}
