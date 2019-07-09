#include <robotx_hardware_interface/gazebo_interface.h>

GazeboInterface::GazeboInterface(ros::NodeHandle nh,ros::NodeHandle pnh) : InterfaceBase(nh,pnh)
{
    left_thrust_cmd_pub_ = nh_.advertise<std_msgs::Float32>("left_thrust_cmd",1);
    right_thrust_cmd_pub_ = nh_.advertise<std_msgs::Float32>("right_thrust_cmd",1);
    left_thrust_angle_pub_ = nh_.advertise<std_msgs::Float32>("left_thrust_angle",1);
    right_thrust_angle_pub_ = nh_.advertise<std_msgs::Float32>("right_thrust_angle",1);
}

GazeboInterface::~GazeboInterface()
{

}

void GazeboInterface::sendCommandToTheTarget(usv_control_msgs::AzimuthThrusterCatamaranDriveStamped msg)
{
    std_msgs::Float32 pub_msg;
    pub_msg.data = msg.command.left_thrust_cmd;
    left_thrust_cmd_pub_.publish(pub_msg);
    pub_msg.data = msg.command.right_thrust_cmd;
    right_thrust_cmd_pub_.publish(pub_msg);
    pub_msg.data = msg.command.left_thrust_angle;
    left_thrust_angle_pub_.publish(pub_msg);
    pub_msg.data = msg.command.right_thrust_angle;
    right_thrust_angle_pub_.publish(pub_msg);
}