cmake_minimum_required(VERSION 3.5)
project(path_sketch)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic 
  -O3 -mtune=native -march=native
  -g -ggdb
  )
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rcutils)
find_package(nav_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

include_directories(
  include
)

add_library(path_sketch SHARED src/path_sketch.cpp)
ament_target_dependencies(path_sketch rclcpp rcutils sensor_msgs nav_msgs geometry_msgs)

rclcpp_components_register_node(
  path_sketch
  PLUGIN "filter::PathSketch"
  EXECUTABLE PathSketchExecutable)

install(TARGETS path_sketch
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install launch files.
install(DIRECTORY
  params
  DESTINATION share/${PROJECT_NAME}/
)

# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
