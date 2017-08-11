cmake_minimum_required(VERSION 2.8.3)
project(rviz_demoscene)
add_compile_options(-std=c++11)
find_package(catkin REQUIRED std_msgs roscpp geometry_msgs)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(demonode src/translator.cpp)
target_link_libraries(demonode ${catkin_LIBRARIES})
