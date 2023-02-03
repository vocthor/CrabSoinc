cmake_minimum_required(VERSION 3.8)
project(robot)

# Default to C11
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rcl REQUIRED)
find_package(rclc REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(roverc REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(algo_node src/algo_node.cpp)
ament_target_dependencies(algo_node rclcpp geometry_msgs std_msgs roverc)
add_executable(motor_controller src/motor_controller.cpp)
ament_target_dependencies(motor_controller rclcpp geometry_msgs std_msgs roverc)

install(TARGETS 
  algo_node
  motor_controller
  DESTINATION lib/${PROJECT_NAME}) 

ament_package()
