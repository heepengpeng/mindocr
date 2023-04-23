#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <cstdint>
#include <list>
#include <mutex>

static const int DEFAULT_MAX_QUEUE_SIZE = 256;

template <typename T>
class BlockingQueue{
public:
    BlockingQueue(uint32_t maxSize = DEFAULT_MAX_QUEUE_SIZE) : m_max_size(maxSize), m_is_stopped(false){};
    ~BlockingQueue();

private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    uint32_t m_max_size;
    bool m_is_stopped;
};
#endif