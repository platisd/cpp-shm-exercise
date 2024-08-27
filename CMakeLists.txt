cmake_minimum_required(VERSION 3.13)
project(TakeItToProduction)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(external)

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
)

add_executable(data_creator_writer_shm example/data_creator_writer_shm.cpp)
target_link_libraries(data_creator_writer_shm PUBLIC boost rt pthread)

add_executable(data_reader_writer_shm example/data_reader_writer_shm.cpp)
target_link_libraries(data_reader_writer_shm PUBLIC boost rt pthread)

enable_testing()
add_subdirectory(test)
