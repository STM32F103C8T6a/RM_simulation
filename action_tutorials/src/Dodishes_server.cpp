#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include "action_tutorials/DodishesAction.h"

typedef actionlib::SimpleActionServer<action_tutorials::DodishesAction> Server;


void execute(const action_tutorials::DodishesGoalConstPtr& goal, Server* as)
{
    ros::Rate r(1);
    action_tutorials::DodishesFeedback feedback;
    ROS_INFO("dishwater %d is working", goal->dishwasher_id);

    //洗盘子的进度，按照1hz的频率b发布进度feedback
    for(int i= 2; i<=10 ;i++)
    {
        feedback.percent_complete = i * 10;
        as->publishFeedback(feedback);
        r.sleep();
    }

    //action ends and return the result to client
    ROS_INFO("dishwater %d finish working", goal->dishwasher_id);
    as->setSucceeded();
}
int main(int argc, char *argv[])
{
    ros::init(argc, argv,"do_dishes_server");
    ros::NodeHandle nh;

    //define a server;
    Server server(nh, "do_dishes", boost::bind(&execute, _1, &server),false);

    //server begins
    server.start();
    ros::spin();
    return 0;
}
