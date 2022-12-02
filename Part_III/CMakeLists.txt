cmake_minimum_required(VERSION 2.8)
project(IC_G07_Proj2)

SET (BASE_DIR ${CMAKE_SOURCE_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR} /../Part_III/test_programs)

add_library(audioCodec 
    audioCodec.hpp
    audioCodec.cpp
)
target_link_libraries(audioCodec sndfile)

add_executable (testEncoding ./test_programs/testEncoding.cpp)
target_link_libraries (testEncoding sndfile)

add_executable (testDecoding ./test_programs/testDecoding.cpp)
target_link_libraries (testDecoding sndfile)