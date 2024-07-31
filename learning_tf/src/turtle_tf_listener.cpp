#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"my_tf_listener");
    ros::NodeHandle nh;
    
    //generate second turtle
    ros::service::waitForService("spawn");
    ros::ServiceClient add_turtle = nh.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    ros::Publisher turtle_vel = nh.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",10);

    //tf监听器
    tf::TransformListener listener;
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        tf::StampedTransform transform;
        try
        {
            //查找turtle1 与turtle2 的坐标变换
            listener.waitForTransform("/turtle2","/turtle1",ros::Time(0),ros::Duration(3.0));
            listener.lookupTransform("/turtle2","/turtle1",ros::Time(0),transform);
        }
        catch(tf::TransformException &ex)
        {
            ROS_ERROR("%s", ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        //根据坐标转换，计算turtle2需要的运动线速度和角速度      并发布
        geometry_msgs::Twist vel_msg;
        vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(),2) + sqrt(pow(transform.getOrigin().y(),2)));
        vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(),transform.getOrigin().x());
        turtle_vel.publish(vel_msg);
        loop_rate.sleep();
    }
    return 0;
}
