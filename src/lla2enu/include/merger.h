//
// Created by ma on 23-8-17.
//

#ifndef LLA2ENU_MERGER_H
#define LLA2ENU_MERGER_H

#include "opencv2/opencv.hpp"
#include <Eigen/Dense>

class map_merge
{
public:
    cv::Mat rot_matrix(const cv::Mat& image1, const cv::Mat& image2);
};


#endif //LLA2ENU_MAP_MERGE_H
