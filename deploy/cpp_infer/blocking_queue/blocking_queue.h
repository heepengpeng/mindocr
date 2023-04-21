
#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H
#include <cstdint>
#include <list>
#include <mutex>
static const int DEFAULT_MAX_QUEUE_SIZE = 256;
template <typename T>
class BlockingQueue
{
public:
    BlockingQueue(uint32_t maxSize = DEFAULT_MAX_QUEUE_SIZE) : max_size_(maxSize), is_stopped(false){};

private:
    std::list<T> queue_;
    std::mutex mutex_;
    bool is_stopped;
};
#enif