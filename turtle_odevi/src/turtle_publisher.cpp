#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_hareket_yayinci");
    ros::NodeHandle n;

    
    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    
    
    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        geometry_msgs::Twist hiz_mesaji;
        
        
        hiz_mesaji.linear.x = 1.0;   
        hiz_mesaji.angular.z = 0.5;  
        
        vel_pub.publish(hiz_mesaji);
        
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}