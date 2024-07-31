#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <dynamic_tutorials/tutorialsConfig.h>

void callback(dynamic_tutorials::tutorialsConfig& config, uint32_t level){
    ROS_INFO("Reconfig Request: %d ,%.2f ,%s ,%d ,%d",
            config.int_param,  config.double_param,
            config.string_param.c_str(), config.bool_param,
            config.list_param);
}
int main(int argc, char *argv[])
{
    ros::init(argc,argv,"dynamic_tutorials");

    dynamic_reconfigure::Server<dynamic_tutorials::tutorialsConfig> server;

    dynamic_reconfigure::Server<dynamic_tutorials::tutorialsConfig>::CallbackType f;
    f = boost::bind(&callback,_1,_2);
    server.setCallback(f);
    ROS_INFO("Spinning the node");
    ros::spin();
    return 0;
}
