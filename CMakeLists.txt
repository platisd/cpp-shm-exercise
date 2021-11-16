cmake_minimum_required(VERSION 3.13)
project(TakeItToProduction)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(
        -Wcast-align
        -Wpedantic
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wnon-virtual-dtor
        -Wmissing-include-dirs
        -Wdisabled-optimization
        -Winit-self
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wparentheses
        -Wredundant-decls
        -Wshadow
        -Wsign-promo
        -Wstrict-aliasing
        -Wall
        -Wextra
        -Werror
)

add_subdirectory(external)

get_target_property(boost_include_dirs boost INTERFACE_INCLUDE_DIRECTORIES)

add_executable(data_creator_writer_shm example/data_creator_writer_shm.cpp)
target_include_directories(data_creator_writer_shm SYSTEM PUBLIC ${boost_include_dirs})
target_link_libraries(data_creator_writer_shm PUBLIC rt pthread)

add_executable(data_reader_writer_shm example/data_reader_writer_shm.cpp)
target_include_directories(data_reader_writer_shm SYSTEM PUBLIC ${boost_include_dirs})
target_link_libraries(data_reader_writer_shm PUBLIC rt pthread)

enable_testing()
add_subdirectory(test)
