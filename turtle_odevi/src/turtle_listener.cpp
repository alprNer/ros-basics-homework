#include "ros/ros.h"
#include "turtlesim/Pose.h"


void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
    
    ROS_INFO("Konum -> X: %.2f, Y: %.2f, Aci: %.2f", msg->x, msg->y, msg->theta);
}

int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "turtle_konum_dinleyici");
    ros::NodeHandle n;

    
    ros::Subscriber sub = n.subscribe("/turtle1/pose", 10, poseCallback);

    
    ros::spin();

    return 0;
}