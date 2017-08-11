cmake_minimum_required(VERSION 2.8.3)
project(rviz_demoscene)
add_compile_options(-std=c++11)
find_package(catkin REQUIRED std_msgs visualization_msgs roscpp)

catkin_package(
  CATKIN_DEPENDS roscpp visualization_msgs std_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(demonode src/translator.cpp)
target_link_libraries(demonode ${catkin_LIBRARIES})
