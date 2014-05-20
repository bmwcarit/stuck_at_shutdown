cmake_minimum_required(VERSION 2.8.3)
project(stuck_at_shutdown)

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(stuck_at_shutdown ./src/stuck_at_shutdown.cpp)
target_link_libraries(stuck_at_shutdown ${catkin_LIBRARIES})

