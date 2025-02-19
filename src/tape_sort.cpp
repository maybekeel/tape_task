#include "tape_sort.hpp"

#include <math.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <thread>

TapeSorter::TapeSorter(
    const std::shared_ptr<ITapeCreator>& creator)
    : _creator(creator) {}

void TapeSorter::sort(
    const std::shared_ptr<tape::ITape>& in,
    const std::shared_ptr<tape::ITape>& out,
    const size_t m) {
    std::thread reader(&TapeSorter::_read, this, in, m);
    std::thread sorter(&TapeSorter::_sort, this);
    std::thread merger(&TapeSorter::_merge, this, out);

    reader.join();
    sorter.join();
    merger.join();
}

void TapeSorter::_read(
    const std::shared_ptr<tape::ITape>& in,
    const size_t m) {
    auto buf_size = std::floor(m / sizeof(tape::type));
    while (!in->is_end()) {
        std::vector<tape::type> buffer;
        size_t i = 0;
        while (i++ < buf_size && !in->is_end()) {
            buffer.emplace_back(in->read());
            in->move_forward();
        }
        if (!buffer.empty()) {
            std::sort(buffer.begin(), buffer.end());
            {
                std::lock_guard<std::mutex> lock(queue_mutex);
                buffer_queue.push(std::move(buffer));
            }
            queue_cv.notify_one();
        }
    }
    {
        finished_reading = true;
    }
    queue_cv.notify_one(); 
}

void TapeSorter::_sort() {
    while (true) {
        std::vector<tape::type> buffer;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            queue_cv.wait(lock, [this] { return !buffer_queue.empty() || finished_reading; });

            if (buffer_queue.empty() && finished_reading) {
                break;
            }
            buffer = std::move(buffer_queue.front());
            buffer_queue.pop();
        }
        auto tmp = _creator->create();
        for (const auto& el : buffer) {
            tmp->write(el);
            tmp->move_forward();
        }
        tmp->rewind();
        {
            std::lock_guard<std::mutex> lock(tmp_mutex);
            _tmp_tapes.emplace_back(tmp);
            tmp_cv.notify_one();
        }
    }
    {
        finished_filling = true;
    }
}

void TapeSorter::_merge(
    const std::shared_ptr<tape::ITape>& out) {
    std::shared_ptr<tape::ITape> first;
    std::shared_ptr<tape::ITape> second;
    while (true) {
        {
            std::unique_lock<std::mutex> lock(tmp_mutex);
            tmp_cv.wait(lock, [this] { return !_tmp_tapes.empty() || finished_filling; });
            if (finished_filling) {
                if  (_tmp_tapes.size() == 2) {
                    first = _tmp_tapes.at(0);
                    second = _tmp_tapes.at(1);
                    lock.unlock();
                    _mergesort(first, second, out);
                }
                break;
            }
            if (_tmp_tapes.size() == 1) {
                continue;
            }
            first = _tmp_tapes.at(0);
            second = _tmp_tapes.at(1);
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
}

void TapeSorter::_mergesort(
    const std::shared_ptr<tape::ITape>& first,
    const std::shared_ptr<tape::ITape>& second,
    const std::shared_ptr<tape::ITape>& out) {
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