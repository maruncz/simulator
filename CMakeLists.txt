cmake_minimum_required(VERSION 3.14)

project(simulator LANGUAGES CXX)

include(FetchContent)

option(ENABLE_BENCHMARK OFF)
option(ENABLE_TESTS OFF)

add_subdirectory(src)
if(${ENABLE_BENCHMARK})
    add_subdirectory(bench)
endif()

if(${ENABLE_TESTS})
    add_subdirectory(tests)
endif()
