cmake_minimum_required(VERSION 2.8.3)
project(transform)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
roscpp
rospy
std_msgs
geometry_msgs
tf
nav_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES mybot_control
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(lasertf src/lasertf.cpp)
target_link_libraries(lasertf ${catkin_LIBRARIES})

add_executable(zedtf src/zedtf.cpp)
target_link_libraries(zedtf ${catkin_LIBRARIES})

add_executable(odomtf src/odomtf.cpp)
target_link_libraries(odomtf ${catkin_LIBRARIES})
