cmake_minimum_required(VERSION 2.8.3)
project(balance_robot_description)

find_package(catkin REQUIRED COMPONENTS
  rospy
  geometry_msgs
  roscpp
  rospy
  std_msgs
  sensor_msgs
  nav_msgs
  tf
  control_msgs
  dynamic_reconfigure
)

generate_dynamic_reconfigure_options(
  cfg/gain.cfg
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(balance_robot_control 
  src/control_main.cpp
  src/balance_robot_control.hpp
  src/balance_robot_control.cpp
)

add_dependencies(balance_robot_control ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(balance_robot_control
  ${catkin_LIBRARIES}
)