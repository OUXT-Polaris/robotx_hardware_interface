#include <robotx_hardware_interface/interface_base.h>

InterfaceBase::InterfaceBase(ros::NodeHandle nh,ros::NodeHandle pnh)
{
    nh_ = nh;
    pnh_ = pnh;
    pnh_.param<std::string>("robot_frame", robot_frame_, "base_link");
    pnh_.param<double>("output_rate", output_rate_, 30);
    marker_pub_ = pnh_.advertise<visualization_msgs::MarkerArray>("marker",1);
    cmd_sub_ = nh_.subscribe("/motor_command",1,&InterfaceBase::motorCommandCallback,this);
}

InterfaceBase::~InterfaceBase()
{

}

void InterfaceBase::motorCommandCallback(const usv_control_msgs::AzimuthThrusterCatamaranDriveStamped::ConstPtr msg)
{
    mtx_.lock();
    cmd_ = *msg;
    marker_pub_.publish(generateMarker());
    mtx_.unlock();
}

visualization_msgs::MarkerArray InterfaceBase::generateMarker()
{
    visualization_msgs::MarkerArray marker_msg;
    double marker_position_x = -2.5;
    double marker_position_y =  1.5;
    double marker_position_z =  0.0;
    double marker_size = 0.2;
    geometry_msgs::Quaternion quat;
    quat.x = 0.0;
    quat.y = 0.0;
    quat.z = 0.0;
    quat.w = 1.0;
    geometry_msgs::Vector3 vec;
    vec.x = 0.0;
    vec.y = M_PI/2;
    vec.z = 0.0;
    if(cmd_)
    {
        if(!isEquals(cmd_->command.left_thrust_cmd,0.0))
        {
            visualization_msgs::Marker left_thrust_marker;
            left_thrust_marker.header.frame_id = robot_frame_;
            left_thrust_marker.header.stamp = cmd_->header.stamp;
            left_thrust_marker.ns = "left_thrust";
            left_thrust_marker.id = 0;
            left_thrust_marker.type = visualization_msgs::Marker::CYLINDER;
            left_thrust_marker.action = visualization_msgs::Marker::ADD;
            left_thrust_marker.pose.position.x = marker_position_x;
            left_thrust_marker.pose.position.y = marker_position_y;
            left_thrust_marker.pose.position.z = marker_position_z+cmd_->command.left_thrust_cmd*0.5;
            left_thrust_marker.pose.orientation = quat;//*quaternion_operation::convertEulerAngleToQuaternion(vec);
            left_thrust_marker.scale.x = marker_size;
            left_thrust_marker.scale.y = marker_size;
            left_thrust_marker.scale.z = -1*cmd_->command.left_thrust_cmd;
            if(cmd_->command.left_thrust_cmd>0.0)
            {
                left_thrust_marker.color.r = 0.3;
                left_thrust_marker.color.g = 1.0;
                left_thrust_marker.color.b = 0.3;
                left_thrust_marker.color.a = 0.8;
            }
            else
            {
                left_thrust_marker.color.r = 1.0;
                left_thrust_marker.color.g = 0.3;
                left_thrust_marker.color.b = 0.3;
                left_thrust_marker.color.a = 0.8;
            }
            left_thrust_marker.frame_locked = true;
            left_thrust_marker.lifetime = ros::Duration(0.1);
            marker_msg.markers.push_back(left_thrust_marker);
        }
        if(!isEquals(cmd_->command.right_thrust_cmd,0.0))
        {
            visualization_msgs::Marker right_thrust_marker;
            right_thrust_marker.header.frame_id = robot_frame_;
            right_thrust_marker.header.stamp = cmd_->header.stamp;
            right_thrust_marker.ns = "right_thrust";
            right_thrust_marker.id = 0;
            right_thrust_marker.type = visualization_msgs::Marker::CYLINDER;
            right_thrust_marker.action = visualization_msgs::Marker::ADD;
            right_thrust_marker.pose.position.x = marker_position_x;
            right_thrust_marker.pose.position.y = -marker_position_y;
            right_thrust_marker.pose.position.z = marker_position_z+cmd_->command.right_thrust_cmd*0.5;
            right_thrust_marker.pose.orientation = quat;//*quaternion_operation::convertEulerAngleToQuaternion(vec);
            right_thrust_marker.scale.x = marker_size;
            right_thrust_marker.scale.y = marker_size;
            right_thrust_marker.scale.z = -1*cmd_->command.right_thrust_cmd;
            if(cmd_->command.right_thrust_cmd>0.0)
            {
                right_thrust_marker.color.r = 0.3;
                right_thrust_marker.color.g = 1.0;
                right_thrust_marker.color.b = 0.3;
                right_thrust_marker.color.a = 0.8;
            }
            else
            {
                right_thrust_marker.color.r = 1.0;
                right_thrust_marker.color.g = 0.3;
                right_thrust_marker.color.b = 0.3;
                right_thrust_marker.color.a = 0.8;
            }
            right_thrust_marker.frame_locked = true;
            right_thrust_marker.lifetime = ros::Duration(0.1);
            marker_msg.markers.push_back(right_thrust_marker);
        }
    }
    return marker_msg;
}

void InterfaceBase::run()
{
    boost::thread thread_send(boost::bind(&InterfaceBase::sendCommand, this));
}

void InterfaceBase::sendCommand()
{
    while(ros::ok())
    {
        ros::Rate rate(output_rate_);
        if(cmd_)
        {
            mtx_.lock();
            try
            {
                sendCommandToTheTarget(*cmd_);
            }
            catch(std::exception& e)
            {
                ROS_WARN_STREAM(e.what());
            }
            mtx_.unlock();
        }
        rate.sleep();
    }
}