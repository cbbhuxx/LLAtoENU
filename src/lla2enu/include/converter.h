//
// Created by ma on 23-8-17.
//

#ifndef LLA2ENU_CONVERTER_H
#define LLA2ENU_CONVERTER_H

#include <cmath>
#include <sensor_msgs/NavSatFix.h>

#define PI 3.1415926

class converter
{
private:
    float lon0, lat0, alt0;
    float* arr;
    float* arr1;

public:
    converter()
    {
        arr = new float[3];
        arr1 = new float[3];
    }
    void convert_init(float a, float b, float c);
    float* lla2xyz(float lon, float lat, float alt);
    float* xyz2enu(float x1, float y1, float z1, float x2, float y2, float z2);
    float* lla2enu(const sensor_msgs::NavSatFix& gps);
    ~converter()
    {
        delete arr, arr1;
        arr = nullptr;
        arr1 = nullptr;
    };
};

#endif //LLA2ENU_CONVERTER_H
