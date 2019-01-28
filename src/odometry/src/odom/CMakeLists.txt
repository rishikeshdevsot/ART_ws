cmake_minimum_required(VERSION 2.8.3)
project(odom)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
roscpp
rospy
std_msgs
nav_msgs
geometry_msgs
tf
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES mybot_control
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(odom src/odom.cpp)
target_link_libraries(odom ${catkin_LIBRARIES})


