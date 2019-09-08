#ifndef ROBOTX_HARDWARE_INTERFACE_INTERFACE_BASE_H_INCLUDED
#define ROBOTX_HARDWARE_INTERFACE_INTERFACE_BASE_H_INCLUDED

// Headers in ROS
#include <ros/ros.h>
#include <usv_control_msgs/AzimuthThrusterCatamaranDriveStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <quaternion_operation/quaternion_operation.h>

// Headers in Boost
#include <boost/optional.hpp>
#include <boost/thread.hpp>

// Headers in STL
#include <mutex>
#include <float.h>

class InterfaceBase
{
public:
    InterfaceBase(ros::NodeHandle nh,ros::NodeHandle pnh);
    ~InterfaceBase();
    void run();
protected:
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
private:
    virtual void sendCommandToTheTarget(usv_control_msgs::AzimuthThrusterCatamaranDriveStamped msg) = 0;
    void currentCommandCallback(const usv_control_msgs::AzimuthThrusterCatamaranDriveStamped::ConstPtr msg);
    boost::optional<usv_control_msgs::AzimuthThrusterCatamaranDriveStamped> cmd_;
    void sendCommand();
    double output_rate_;
    ros::Subscriber cmd_sub_;
    std::mutex mtx_;
    ros::Publisher marker_pub_;
    visualization_msgs::MarkerArray generateMarker();
    std::string robot_frame_;
    inline bool isEquals(double a,double b)
    {
        if (fabs(a - b) <= DBL_EPSILON * fmax(1, fmax(fabs(a), fabs(b))))
        {
            return true;
        }
        return false;
    }
};

#endif  //ROBOTX_HARDWARE_INTERFACE_INTERFACE_BASE_H_INCLUDED