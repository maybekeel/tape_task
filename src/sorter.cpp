#include "sorter.hpp"

#include <math.h>

#include <algorithm>
#include <cstdio>
#include <thread>

tape::Sorter::Sorter(
    const std::shared_ptr<ICreator>& creator)
    : _creator(creator) {}

void tape::Sorter::sort(const std::shared_ptr<ITape>& in,
                        const std::shared_ptr<ITape>& out,
                        const size_t n, const size_t m) {
    auto buf_size = std::floor(m / sizeof(tape::type));
    if (buf_size >= n) {
        _small_sort(in, out, buf_size);
        return;
    }
    std::thread reader(&Sorter::_read, this, in, buf_size);
    std::thread merger(&Sorter::_merge, this, out);

    reader.join();
    merger.join();
}

void tape::Sorter::_small_sort(
    const std::shared_ptr<ITape>& in,
    const std::shared_ptr<ITape>& out,
    const size_t buf_size) {
    std::vector<type> buffer;
    _fill_buffer(in, buffer, buf_size);
    if (buffer.empty()) {
        return;
    }
    std::sort(buffer.begin(), buffer.end());
    std::for_each(buffer.begin(), buffer.end(),
                  [&](const type val) {
                      out->write(val);
                      out->move_forward();
                  });
}

void tape::Sorter::_read(
    const std::shared_ptr<tape::ITape>& in,
    const size_t buf_size) {
    std::vector<tape::type> buffer;
    while (!in->is_end()) {
        _fill_buffer(in, buffer, buf_size);
        _sort_buffer(buffer);
    }
    _finish = true;
    _cv.notify_one();
}

void tape::Sorter::_sort_buffer(std::vector<type>& buffer) {
    if (!buffer.empty()) {
        std::sort(buffer.begin(), buffer.end());
    }
    auto tmp = _creator->create();
    for (const auto& el : buffer) {
        tmp->write(el);
        tmp->move_forward();
    }
    buffer.clear();
    tmp->rewind();
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _tmp_tapes.emplace_back(tmp);
        _cv.notify_one();
    }
}
void tape::Sorter::_merge(
    const std::shared_ptr<ITape>& out) {
    while (true) {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [this] {
            return _tmp_tapes.size() >= 2 || _finish;
        });
        if (_finish) {
            lock.unlock();
            _mergesort(_tmp_tapes.at(0), _tmp_tapes.at(1),
                       out);
            break;
        }
        auto first = _tmp_tapes.at(0);
        auto second = _tmp_tapes.at(1);
        lock.unlock();
        auto merged_tape = _creator->create();
        _mergesort(first, second, merged_tape);
        merged_tape->rewind();
        lock.lock();
        _tmp_tapes.emplace_back(merged_tape);
        _tmp_tapes.erase(_tmp_tapes.begin());
        _tmp_tapes.erase(_tmp_tapes.begin());
    }
}

void tape::Sorter::_mergesort(
    const std::shared_ptr<ITape>& first,
    const std::shared_ptr<ITape>& second,
    const std::shared_ptr<ITape>& out) {
    while (!first->is_end() || !second->is_end()) {
        if (!first->is_end() &&
            (second->is_end() ||
             first->read() <= second->read())) {
            out->write(first->read());
            first->move_forward();
        } else {
            out->write(second->read());
            second->move_forward();
        }
        out->move_forward();
    }
}

void tape::Sorter::_fill_buffer(
    const std::shared_ptr<ITape>& in,
    std::vector<type>& buffer, const size_t buf_size) {
    size_t i = 0;
    while (i++ < buf_size && !in->is_end()) {
        buffer.emplace_back(in->read());
        in->move_forward();
    }
}
