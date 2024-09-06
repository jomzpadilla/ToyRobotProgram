cmake_minimum_required(VERSION 3.20)
project(ToyRobot)

enable_testing()

add_library(ToyRobotLib src/robot.cpp src/robot.hpp)
target_include_directories(ToyRobotLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ToyRobot src/toyRobot.cpp)
target_link_libraries(ToyRobot PRIVATE ToyRobotLib)

add_subdirectory(test)




