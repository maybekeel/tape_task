#ifndef SORTER_HPP
#define SORTER_HPP

#include <condition_variable>
#include <memory>
#include <vector>

#include "creator.hpp"
#include "tape.hpp"

namespace tape {
class Sorter {
   public:
    Sorter(const std::shared_ptr<ICreator>& creator);
    void sort(const std::shared_ptr<ITape>& in,
              const std::shared_ptr<ITape>& out, size_t n,
              size_t m);

   private:
    std::shared_ptr<ICreator> _creator;
    std::vector<std::shared_ptr<ITape>> _tmp_tapes;

    std::mutex _mutex;
    std::condition_variable _cv;
    std::atomic_bool _finish = false;

    void _read(const std::shared_ptr<ITape>& in, size_t m);
    void _small_sort(const std::shared_ptr<ITape>& in,
                     const std::shared_ptr<ITape>& out,
                     size_t buf_size);
    void _sort_buffer(std::vector<type>& buffer);
    void _merge(const std::shared_ptr<ITape>& out);
    void _mergesort(const std::shared_ptr<ITape>& first,
                    const std::shared_ptr<ITape>& second,
                    const std::shared_ptr<ITape>& out);
    void _fill_buffer(const std::shared_ptr<ITape>& in,
                      std::vector<type>& buffer,
                      size_t buf_size);
};
}  // namespace tape
#endif
