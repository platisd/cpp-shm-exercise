#include "shared_data.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <cstdio>
#include <iostream>

using namespace boost::interprocess;

int main()
{
    // Remove shared memory on destruction
    struct shm_remove
    {
        ~shm_remove()
        {
            shared_memory_object::remove("MySharedMemory");
        }
    } remover;

    // Open the shared memory object.
    shared_memory_object shm(open_only, "MySharedMemory", read_write);

    // Map the whole shared memory in this process
    mapped_region region(shm, read_write);
    // Get the address of the mapped region
    void* addr = region.get_address();

    // Construct the shared structure in memory
    Image* image = static_cast<Image*>(addr);

    {
        std::cout << "Waiting" << std::endl;
        scoped_lock<interprocess_mutex> lock(image->mutex);
        std::cout << "Stopped Waiting" << std::endl;

        for (std::size_t i = 0; i < Image::size; ++i)
        {
            // Lock the mutex
            const auto current_pixel = image->data.at(i);
            image->data.at(i)        = current_pixel + 1;
        }
    }

    return 0;
}