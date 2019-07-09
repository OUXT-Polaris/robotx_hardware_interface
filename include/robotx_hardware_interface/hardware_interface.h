#ifndef ROBOTX_HARDWARE_INTERFACE_HARDWARE_INTERFACE_H_INCLUDED
#define ROBOTX_HARDWARE_INTERFACE_HARDWARE_INTERFACE_H_INCLUDED

#include <robotx_hardware_interface/interface_base.h>

class HardwareInterface : public InterfaceBase
{
public:
    HardwareInterface(ros::NodeHandle nh,ros::NodeHandle pnh);
    ~HardwareInterface();
private:
    void sendCommandToTheTarget(usv_control_msgs::AzimuthThrusterCatamaranDriveStamped msg);
};

#endif  //ROBOTX_HARDWARE_INTERFACE_HARDWARE_INTERFACE_H_INCLUDED