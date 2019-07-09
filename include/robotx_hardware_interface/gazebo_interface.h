#ifndef ROBOTX_HARDWARE_INTERFACE_GAZEBO_INTERFACE_H_INCLUDED
#define ROBOTX_HARDWARE_INTERFACE_GAZEBO_INTERFACE_H_INCLUDED

// Headers in this package
#include <robotx_hardware_interface/interface_base.h>

// Headers in ROS
#include <std_msgs/Float32.h>

class GazeboInterface : public InterfaceBase
{
    GazeboInterface(ros::NodeHandle nh,ros::NodeHandle pnh);
    ~GazeboInterface();
private:
    void sendCommandToTheTarget(usv_control_msgs::AzimuthThrusterCatamaranDriveStamped msg);
    ros::Publisher left_thrust_cmd_pub_;
    ros::Publisher right_thrust_cmd_pub_;
    ros::Publisher left_thrust_angle_pub_;
    ros::Publisher right_thrust_angle_pub_;
};

#endif  //ROBOTX_HARDWARE_INTERFACE_GAZEBO_INTERFACE_H_INCLUDED