cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(../counter
        ${GTEST_INCLUDE_DIRS})

add_executable(test_counter test_counter.cpp)
target_link_libraries(test_counter ${GTEST_LIBRARIES} Threads::Threads counter)

enable_testing()
add_test(NAME TestCounter COMMAND ./test_counter)