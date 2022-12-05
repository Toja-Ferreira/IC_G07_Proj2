cmake_minimum_required(VERSION 3.16)
project(IC_G07_Proj2)


SET (CMAKE_BUILD_TYPE "Release")
#SET (CMAKE_BUILD_TYPE "Debug")

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")
SET (CMAKE_CXX_FLAGS_DEBUG "-g3 -fsanitize=address")

SET (BASE_DIR ${CMAKE_SOURCE_DIR} )
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/../bin)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )



add_executable (test_image_codec test_image_codec.cpp)
target_link_libraries (test_image_codec ${OpenCV_LIBS})