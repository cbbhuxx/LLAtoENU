//
// Created by cbbhuxx on 23-8-17.
//

#include "../include/converter.h"

void converter::convert_init(float a, float b, float c)
{
    lon0 = a;
    lat0 = b;
    alt0 = c;
}

float* converter::lla2xyz(float lon, float lat, float alt)
{
    float LON, LAT, e2, N, a = 6378137.0,b = 6356752.3142;
    LON = lon / 180.0 * PI;
    LAT = lat / 180.0 * PI;

    e2 = (pow(a,2)- pow(b,2)) / pow(a,2);
    N = a / sqrt(1 - e2 * sin(LAT) * sin(LAT));
    arr[0] = (N + alt) * cos(LAT) * cos(LON);
    arr[1] = (N + alt) * cos(LAT) * sin(LON);
    arr[2] = (N * (1 - e2) + alt) * sin(LAT);

    return arr;
}

float* converter::xyz2enu(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float longitude, latitude;
    longitude = lon0 / 180.0 * PI;
    latitude = lat0 / 180.0 * PI;

    arr1[0] = -1 * sin(longitude) * (x2 - x1) + cos(longitude) * (y2 - y1);
    arr1[1] = -1 * sin(latitude) * cos(longitude) * (x2 - x1) - sin(latitude) * sin(longitude) * (y2 - y1) + cos(latitude) * (z2 - z1);
    arr1[2] = cos(latitude) * cos(longitude) * (x2 - x1) + cos(latitude) * sin(longitude) * (y2 - y1) + sin(latitude) * (z2 - z1);
    return arr1;
}

float* converter::lla2enu(const sensor_msgs::NavSatFix& gps)
{
    float* p0 = lla2xyz(lon0,lat0,alt0);
    float x0,y0,z0,x,y,z;
    x0 = p0[0];
    y0 = p0[1];
    z0 = p0[2];
    float* p1 = lla2xyz(gps.longitude,gps.latitude,gps.altitude);
    float* p = xyz2enu(x0, y0, z0, p1[0], p1[1], p1[2]);

    return p;
}

