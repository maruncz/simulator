cmake_minimum_required(VERSION 3.14)

find_package(TBB REQUIRED)

add_library(sim INTERFACE alg.h base.h lti.h pid.h)
target_compile_features(sim INTERFACE cxx_std_20)
target_include_directories(sim INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sim INTERFACE TBB::tbb)
