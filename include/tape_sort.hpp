#ifndef TAPE_SORT_HPP
#define TAPE_SORT_HPP

#include <memory>
#include <vector>
#include <queue>
#include <condition_variable>

#include "tape.hpp"
#include "tape_create.hpp"

class TapeSorter {
   public:
    TapeSorter(
        const std::shared_ptr<ITapeCreator>& creator);
    void sort(const std::shared_ptr<tape::ITape>& in,
              const std::shared_ptr<tape::ITape>& out,
              const size_t m);

   private:
    std::shared_ptr<ITapeCreator> _creator;
    std::vector<std::shared_ptr<tape::ITape>> _tmp_tapes;

    std::queue<std::vector<tape::type>> buffer_queue;
    std::mutex queue_mutex;
    std::mutex tmp_mutex;
    std::condition_variable queue_cv;
    std::condition_variable tmp_cv;
    std::atomic_bool finished_reading = false;
    std::atomic_bool finished_filling = false;

    void _read(const std::shared_ptr<tape::ITape>& in,
               const size_t m);
    void _sort();  
    void _merge(const std::shared_ptr<tape::ITape>& out);  
    void _mergesort(
        const std::shared_ptr<tape::ITape>& first,
        const std::shared_ptr<tape::ITape>& second,
        const std::shared_ptr<tape::ITape>& out);
};

#endif
