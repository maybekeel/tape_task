#include <iostream>
#include <fstream>

#include "config.hpp"
#include "include/file_tape.hpp"
#include "include/tape_sort.hpp"
#include "tape.hpp"
#include "file_tape.hpp"
#include "tape_sort.hpp"

int main(int argc, char** argv)
{
  std::string in_name, out_name;

  if (argc > 2)
  {
    in_name = argv[1];
    out_name = argv[2];
  } else {
    std::cerr << "Bad args\n";
    return 1;
  }
  Config cfg("cfg/tape_task.yml");

  auto in = std::make_shared<tape::FileTape>(cfg.get_delay(), in_name);
  auto out = std::make_shared<tape::FileTape>(cfg.get_delay(), out_name);

  TapeSorter sorter(in, out);
  sorter.sort();

  return 0;
}