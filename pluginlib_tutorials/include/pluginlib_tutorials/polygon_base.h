#ifndef PLUGINLIB_TUTORIALS_POLYGON_BASE_H_
#define PLUGINLIB_TUTORIALS_POLYGON_BASE_H_

namespace polygon_base
{

class RegularPolygon
{

public:
    //pluginlib 要求构造函数时不能带参数，所以定义initialize来完成需要初始化的工作
    virtual void initialize(double side_length) = 0;
    virtual double area() = 0;
    virtual ~RegularPolygon() {}

protected:
    RegularPolygon() {}
};

};
#endif