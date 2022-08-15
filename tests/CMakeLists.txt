cmake_minimum_required(VERSION 3.14)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.12.x)

FetchContent_MakeAvailable(
        googletest)

add_executable(test matrix.cpp)
target_link_libraries(test PRIVATE gtest_main sim)
