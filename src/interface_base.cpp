#include <robotx_hardware_interface/interface_base.h>

InterfaceBase::InterfaceBase(ros::NodeHandle nh,ros::NodeHandle pnh)
{
    nh_ = nh;
    pnh_ = pnh;
    pnh_.param<double>("output_rate", output_rate_, 30);
    nh_.subscribe("/current_command",1,&InterfaceBase::currentCommandCallback,this);
}

InterfaceBase::~InterfaceBase()
{

}

void InterfaceBase::currentCommandCallback(const usv_control_msgs::AzimuthThrusterCatamaranDriveStamped::ConstPtr msg)
{
    cmd_ = *msg;
}

void InterfaceBase::run()
{
    
}

void InterfaceBase::sendCommand()
{
    while(ros::ok())
    {
        ros::Rate rate(output_rate_);
        if(cmd_)
        {
            sendCommandToTheTarget(*cmd_);
        }
        rate.sleep();
    }
}