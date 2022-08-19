cmake_minimum_required(VERSION 3.13)

include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "")

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.7.0)

FetchContent_MakeAvailable(
        googlebenchmark)

find_package(TBB REQUIRED)

add_executable(sim-bench bench.cpp)
target_link_libraries(sim-bench PRIVATE benchmark::benchmark_main sim)

add_executable(matrix-bench matrix_bench.cpp)
target_link_libraries(matrix-bench PRIVATE benchmark::benchmark_main sim)
