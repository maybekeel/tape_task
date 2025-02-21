#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>

#include "config.hpp"
#include "creator.hpp"
#include "file_tape.hpp"
#include "file_tape_creator.hpp"
#include "sorter.hpp"
#include "tape.hpp"

int main(int argc, char** argv) {
    auto start = std::chrono::high_resolution_clock::now();
    if (argc < 5) {
        std::cerr << "Bad args\n";
        return 1;
    }
    std::string in_name{argv[1]};
    std::string out_name{argv[2]};
    std::string cfg_path{argv[3]};
    size_t n = std::stoul(argv[4]);
    size_t m = std::stoul(argv[5]);
    auto cfg = std::make_shared<Config>(cfg_path);

    auto in = std::make_shared<tape::FileTape>(
        cfg->get_delay(), in_name);
    auto out = std::make_shared<tape::FileTape>(
        cfg->get_delay(), out_name);

    auto creator =
        std::make_shared<tape::FileTapeCreator>(cfg);
    tape::Sorter sorter(creator);
    sorter.sort(in, out, n, m);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<
        std::chrono::milliseconds>(end - start);
    std::cout << "Execution time: " << duration.count()
              << " ms" << std::endl;
    return 0;
}
