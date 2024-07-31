#include "ros/ros.h"
#include "learning_communication/AddTwoInts.h"

bool add(learning_communication::AddTwoInts::Request &req,
         learning_communication::AddTwoInts::Response &res)
{
    res.sum = req.a + req.b;
    ROS_INFO("requset: x=%1d y=%1d", (long int)req.a , (long int)req.b);
    ROS_INFO("sending back response: [%1d]", (long int)res.sum);
    return true;
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"add_two_int_server");
    ros::NodeHandle nh;
    ros::ServiceServer service = nh.advertiseService("add_two_ints",add);
    ROS_INFO("Ready to add ints");
    ros::spin();
    return 0;
}
