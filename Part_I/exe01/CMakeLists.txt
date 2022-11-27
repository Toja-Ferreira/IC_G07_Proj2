cmake_minimum_required(VERSION 2.8)
project(IC_G07_Proj2)

SET (BASE_DIR ${CMAKE_SOURCE_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR} /../exe01/test_programs)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(copyImage copyImage.cpp )
target_link_libraries(copyImage ${OpenCV_LIBS})

