cmake_minimum_required(VERSION 2.8)
project(IC_G07_Proj2)

SET (BASE_DIR ${CMAKE_SOURCE_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR} /../Part_II/test_programs)

add_executable(test ./test_programs/test.cpp)