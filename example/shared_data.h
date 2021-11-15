#ifndef CPPPROJECT_SHARED_DATA_H
#define CPPPROJECT_SHARED_DATA_H

#include <array>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

struct shared_memory_log
{
    enum
    {
        NumItems = 100
    };
    enum
    {
        LineSize = 100
    };

    shared_memory_log()
        : current_line(0)
        , end_a(false)
        , end_b(false)
    {
    }

    // Mutex to protect access to the queue
    boost::interprocess::interprocess_mutex mutex;

    // Items to fill
    char items[NumItems][LineSize];
    int current_line;
    bool end_a;
    bool end_b;
};

struct Image
{
    static constexpr int width{600};
    static constexpr int height{800};
    static constexpr int size{width * height};
    boost::interprocess::interprocess_mutex mutex;
    std::array<int, size> data;
};
#endif // CPPPROJECT_SHARED_DATA_H
