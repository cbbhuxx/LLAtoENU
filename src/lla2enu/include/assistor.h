//
// Created by ma on 23-8-17.
//

#ifndef LLA2ENU_ASSISTOR_H
#define LLA2ENU_ASSISTOR_H

#include <ros/ros.h>
#include <Eigen/Dense>
//#include "opencv2/opencv.hpp"
#include <nav_msgs/OccupancyGrid.h>
#include <enu_msgs/enu.h>
#include <enu_msgs/multi_enus.h>

class assistor
{
private:
    std::string name;
    ros::NodeHandle nh;
    ros::Publisher pose_pub = nh.advertise<enu_msgs::multi_enus>(name, 1);
public:
    assistor(std::string name1)
    {
        name = name1;
    }
//    void pub_msgs(float* enu, Eigen::Quaterniond qua);  // 发布位姿
    void pub_msgs(float* enu0, float* enu1, float* enu2);  // 发布位置
//    cv::Mat occupancyGridToImage(const nav_msgs::OccupancyGrid::ConstPtr& map); // 栅格地图转Image
//    Eigen::Quaterniond mat2qua(cv::Mat transMat);
};


#endif //LLA2ENU_ASSISTOR_H
