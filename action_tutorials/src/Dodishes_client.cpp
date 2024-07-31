#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "action_tutorials/DodishesAction.h"

typedef actionlib::SimpleActionClient<action_tutorials::DodishesAction> Client;

//action完成后会调用该函数一次
void doneCb(const actionlib::SimpleClientGoalState& state,
            const action_tutorials::DodishesResultConstPtr& result)
{
    ROS_INFO("the dishes are now clean");
    ros::shutdown();
}

//action激活后会调用该函数一次
void activeCb()
{
    ROS_INFO("goal just went active");
}

//收到feedback后会回调该函数
void feedbackCb(const action_tutorials::DodishesFeedbackConstPtr& feedback)
{
    ROS_INFO("percent_complete : %f", feedback->percent_complete);
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"do_dishes_client");
    
    //define a client
    Client client("de_dishes",true);

    //wait for server
    ROS_INFO("Waiting for the server to start");
    client.waitForServer();
    ROS_INFO("Action server started,sending goal");

    action_tutorials::DodishesGoal goal;
    goal.dishwasher_id = 1;

    //send the goal to action server and set the callback
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

    ros::spin();
    return 0;
}
