cmake_minimum_required(VERSION 2.8.3)
project(robotx_hardware_interface)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  usv_control_msgs
)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES robotx_hardware_interface
  CATKIN_DEPENDS roscpp std_msgs usv_control_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(gazebo_interface_node src/interface_base.cpp src/gazebo_interface_node.cpp src/gazebo_interface.cpp)
target_link_libraries(gazebo_interface_node ${catkin_LIBRARIES})
add_dependencies(gazebo_interface_node usv_control_msgs_generate_messages_cpp)

add_executable(hardware_interface_node src/interface_base.cpp src/hardware_interface_node.cpp src/hardware_interface.cpp)
target_link_libraries(hardware_interface_node ${catkin_LIBRARIES})
add_dependencies(hardware_interface_node usv_control_msgs_generate_messages_cpp)

# install executables/libs
install(TARGETS gazebo_interface_node hardware_interface_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# install headers
install(DIRECTORY include
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY launch
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
        USE_SOURCE_PERMISSIONS)