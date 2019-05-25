cmake_minimum_required(VERSION 3.1)
project(Сomparator)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(counter)

add_executable(comparator main.cpp)
add_subdirectory(counter counter)
target_link_libraries(comparator counter)

enable_testing()
add_subdirectory(test test)

