// Headers in ROS
#include <ros/ros.h>

// Headers in this package
#include <robotx_hardware_interface/gazebo_interface.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "robotx_gazebo_interface_node");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");
    ros::spin();
    return 0;
}