#include "ros/ros.h"
#include "pkg1_package/d_alan.h"
#include <cstdlib>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "alan_hesaplama_istemcisi");

    
    if (argc != 3)
    {
        ROS_INFO("Kullanim: rosrun pkg1_package alan_client <en> <boy>");
        return 1;
    }

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<pkg1_package::d_alan>("dikdortgen_alani_hesapla");
    
    
    pkg1_package::d_alan srv;
    srv.request.en = atof(argv[1]);
    srv.request.boy = atof(argv[2]);

    ROS_INFO("Istek gonderiliyor... En: %.2f, Boy: %.2f", srv.request.en, srv.request.boy);

    if (client.call(srv))
    {
        ROS_INFO("Sonuc: Dikdortgenin alani = %.2f", srv.response.alan);
    }
    else
    {
        ROS_ERROR("Servis basarisiz!");
        return 1;
    }

    return 0;
}