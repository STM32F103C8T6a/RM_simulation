#include "ros/ros.h"
#include "learning_communication/AddTwoInts.h"
#include "cstdlib"

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"add_two_ints_client");
    //从终端命令行获取两个加数
    if(argc != 3){
        ROS_INFO("usage: add_two_ints_client X Y");
        return 1;
    }
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<learning_communication::AddTwoInts>("add_two_ints");
    learning_communication::AddTwoInts srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);
    if(client.call(srv)){
        ROS_INFO("sum: %d",(long int)srv.response.sum);
    }
    else{
        ROS_ERROR("Failed to call service add_two_ints_service");
        return 1;
    }
    return 0;
}

