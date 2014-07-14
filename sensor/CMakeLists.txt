cmake_minimum_required(VERSION 2.8.3)
project(sensor)

#SET(CMAKE_BUILD_TYPE Debug)

## Find catkin and any catkin packages
find_package(
  catkin REQUIRED COMPONENTS
  roscpp
  rospy
  geometry_msgs
  message_generation
  tf
  visualization_msgs
)

## Generate added messages and services
generate_messages(
  DEPENDENCIES
  geometry_msgs
)


## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS
  message_runtime
)




include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Build le_sensor

add_executable(
  le_sensor
  src/le_sensor.cpp
)

target_link_libraries(
  le_sensor
  ${catkin_LIBRARIES}
)


## Build recebe_dados

add_executable(
  recebe_dados
  src/recebe_dados.cpp
)

target_link_libraries(
  recebe_dados
  ${catkin_LIBRARIES}
)


## Build 



add_executable(marca_minas src/marca_minas.cpp)
target_link_libraries(marca_minas ${catkin_LIBRARIES})


## Build 



add_executable(points_sensor src/points_sensor.cpp)
target_link_libraries(points_sensor ${catkin_LIBRARIES})




