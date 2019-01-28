cmake_minimum_required(VERSION 2.8.3)
project(robot_nav)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  ##move_base
  ##my_odom_configuration_dep
  ##my_sensor_configuration_dep
  ##my_tf_configuration_dep
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_robot_name_2dnav
#  CATKIN_DEPENDS move_base my_odom_configuration_dep my_sensor_configuration_dep my_tf_configuration_dep
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

install(DIRECTORY launch/ 
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)

