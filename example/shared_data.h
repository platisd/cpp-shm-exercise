#ifndef CPPPROJECT_SHARED_DATA_H
#define CPPPROJECT_SHARED_DATA_H

#include <array>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

struct Image
{
    static constexpr int width{600};
    static constexpr int height{800};
    static constexpr int size{width * height};
    boost::interprocess::interprocess_mutex mutex;
    std::array<int, size> data;
};
#endif // CPPPROJECT_SHARED_DATA_H
