cmake_minimum_required(VERSION 2.8)
project(IC_G07_Proj2)

SET (BASE_DIR ${CMAKE_SOURCE_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR} /../Part_I/test_programs)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(copyImage copyImage.cpp )
target_link_libraries(copyImage ${OpenCV_LIBS})

add_executable(negativeImage negativeImage.cpp )
target_link_libraries(negativeImage ${OpenCV_LIBS})

add_executable(mirrorImage mirrorImage.cpp )
target_link_libraries(mirrorImage ${OpenCV_LIBS})

add_executable(rotateImage rotateImage.cpp )
target_link_libraries(rotateImage ${OpenCV_LIBS})

add_executable(intensityImage intensityImage.cpp )
target_link_libraries(intensityImage ${OpenCV_LIBS})

