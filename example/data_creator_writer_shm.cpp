#include "shared_data.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <cstdio>
#include <iostream>
#include <thread>

using namespace boost::interprocess;

int main()
{
    try
    {
        // Remove shared memory on construction and destruction
        struct shm_remove
        {
            shm_remove()
            {
                shared_memory_object::remove("MySharedMemory");
            }
            ~shm_remove()
            {
                shared_memory_object::remove("MySharedMemory");
            }
        } remover;

        // Create a shared memory object.
        shared_memory_object shm(create_only, "MySharedMemory", read_write);
        // Set size
        shm.truncate(sizeof(Image));
        // Map the whole shared memory in this process
        mapped_region region(shm, read_write);
        // Get the address of the mapped region
        void* addr = region.get_address();

        // Construct the shared structure in memory
        Image* image = new (addr) Image;

        // Write some pixels
        {
            // Lock the mutex
            scoped_lock<interprocess_mutex> lock(image->mutex);
            image->data.fill(10);
        }

        // Wait until the other process ends
        while (1)
        {
            scoped_lock<interprocess_mutex> lock(image->mutex);
            if (std::all_of(image->data.begin(),
                            image->data.end(),
                            [](auto pixel) { return pixel == 11; }))
            {
                break;
            }
            else
            {
                std::cout << "Waiting" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds{1});
            }
        }
    }
    catch (interprocess_exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
