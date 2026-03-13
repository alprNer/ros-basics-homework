#include "ros/ros.h"
#include "pkg1_package/d_alan.h" 


bool handle_alan_hesapla(pkg1_package::d_alan::Request  &req,
                         pkg1_package::d_alan::Response &res)
{
    if (req.en < 0 || req.boy < 0) {
        ROS_WARN("Lutfen pozitif veri giriniz.");
        res.alan = 0.0;
    } else {
        res.alan = req.en * req.boy;
        ROS_INFO("Alan: %.2f", res.alan);
    }
    
    return true;
}

int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "alan_hesaplama_sunucusu");
    ros::NodeHandle n;

    
    ros::ServiceServer service = n.advertiseService("dikdortgen_alani_hesapla", handle_alan_hesapla);
    
    ROS_INFO("Alan hesaplama sunucusu calisiyor...");
    
    ros::spin();

    return 0;
}