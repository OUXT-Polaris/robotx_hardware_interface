#include <robotx_hardware_interface/hardware_interface.h>

HardwareInterface::HardwareInterface(ros::NodeHandle nh,ros::NodeHandle pnh) : InterfaceBase(nh,pnh)
{

}

HardwareInterface::~HardwareInterface()
{

}

void HardwareInterface::sendCommandToTheTarget(usv_control_msgs::AzimuthThrusterCatamaranDriveStamped msg)
{
    /* ToDo add command function to the RobotX Hardware */
}