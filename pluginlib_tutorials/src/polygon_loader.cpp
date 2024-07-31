#include "ros/ros.h"
#include <pluginlib/class_loader.h>
#include <pluginlib_tutorials/polygon_base.h>

int main(int argc, char *argv[])
{
    //创建一个classloader，用来加载plugin
    pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader("pluginlib_tutorials" , "polygon_base::RegularPolygon");
    try
    {
        //load the plugin Triangle
        boost::shared_ptr<polygon_base::RegularPolygon> triangle = poly_loader.createInstance("polygon_plugins::Triangle");
        //initialize the side_length
        triangle->initialize(10.0);
        ROS_INFO("Triangle area: %.2f", triangle->area());
    }
    catch(const pluginlib::PluginlibException& e)
    {
        ROS_ERROR("the plugin failed to load for some reason Error: %s" , e.what());
        std::cerr << e.what() << '\n';
    }

    try
    {
        //load the plugin Triangle
        boost::shared_ptr<polygon_base::RegularPolygon> square = poly_loader.createInstance("polygon_plugins::Square");
        //initialize the side_length
        square->initialize(10.0);
        ROS_INFO("Square area: %.2f", square->area());
    }
    catch(const pluginlib::PluginlibException& e)
    {
        ROS_ERROR("the plugin failed to load for some reason Error: %s" , e.what());
        std::cerr << e.what() << '\n';
    }
    return 0;
}
