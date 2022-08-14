cmake_minimum_required(VERSION 3.14)

find_package(TBB REQUIRED)

add_library(sim INTERFACE base.h pid.h sys.h tf.h)
target_compile_features(sim INTERFACE cxx_std_20)
target_include_directories(sim INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
