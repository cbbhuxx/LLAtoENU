//
// Created by cbbhuxx on 23-8-17.
//

#include "../include/assistor.h"


void assistor::pub_msgs(float* enu0, float* enu1, float* enu2)
{
    enu_msgs::multi_enus mul_enus;
    enu_msgs::enu ENU;
    float *enu_all[3];
    enu_all[0] = enu0;
    enu_all[1] = enu1;
    enu_all[2] = enu2;
    for (int i=0; i<3; i++)
    {
        ENU.id = i;
        ENU.x = enu_all[i][0];
        ENU.y = enu_all[i][1];
        ENU.z = enu_all[i][2];
        mul_enus.data.push_back(ENU);
    }

    pose_pub.publish(mul_enus);
}

//cv::Mat assistor::occupancyGridToImage(const nav_msgs::OccupancyGrid::ConstPtr& map)
//{
//    int width = map->info.width;
//    int height = map->info.height;
//
//    cv::Mat image(height, width, CV_8UC1);
//
//    for (int y = 0; y < height; ++y)
//    {
//        for (int x = 0; x < width; ++x)
//        {
//            int index = x + y * width;
//            int value = map->data[index];
//
//            if (value == 0)
//                image.at<uchar>(y, x) = 255;  // 未知区域
//            else if (value == 100)
//                image.at<uchar>(y, x) = 0;    // 障碍物
//            else
//                image.at<uchar>(y, x) = 127;  // 自由空间
//        }
//    }
//
//    return image;
//}
//
//Eigen::Quaterniond assistor::mat2qua(cv::Mat transMat)
//{
//    Eigen::Matrix3d matrix;
//    for (int i = 0; i < 3; ++i)
//    {
//        for (int j = 0; j < 3; ++j)
//        {
//            matrix(i, j) = transMat.at<double>(i, j);
//        }
//    }
//
//    Eigen::Quaterniond quaternion;
//    quaternion = Eigen::Quaterniond(matrix);
//
//    return quaternion;
//}