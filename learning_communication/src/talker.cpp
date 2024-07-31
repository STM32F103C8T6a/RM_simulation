#include "ros/ros.h"
#include <sstream>
#include "std_msgs/String.h"

int main(int argc, char  *argv[])
{
    ros::init(argc,argv,"talker");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",1000);
    ros::Rate loop_rate(10);
    int count = 0;
    while(ros::ok())
    {
        std_msgs::String msg;
        std::stringstream ss;
        ss << "helloworld" << count;
        msg.data = ss.str();
        ROS_INFO("%s",msg.data.c_str());
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }
    return 0;
}
