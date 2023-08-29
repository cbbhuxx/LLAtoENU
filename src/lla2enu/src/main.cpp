//
// Created by cbbhuxx on 23-8-17.
//

#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/NavSatFix.h>
#include <../include/converter.h>
#include <enu_msgs/enu.h>
#include <enu_msgs/multi_enus.h>
#include "iostream"

bool flag = true;   // 坐标系起点初始化标志位
converter* convert_ptr = new converter();
ros::Publisher pose_pub;

void pub_msgs(float* enu0, float* enu1, float* enu2)
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


void callback(const sensor_msgs::NavSatFix::ConstPtr& gps0, const sensor_msgs::NavSatFix::ConstPtr& gps1, const sensor_msgs::NavSatFix::ConstPtr& gps2)
{
//    ROS_INFO("ROS is running!");
    sensor_msgs::NavSatFix rtk0, rtk1, rtk2;
    rtk0 = *gps0;
    rtk1 = *gps1;
    rtk2 = *gps2;
    if (flag)
    {
        float lon0, lat0, alt0;  //机器人0起始经纬高
        lon0 = rtk0.longitude;
        lat0 = rtk0.latitude;
        alt0 = rtk0.altitude;
        convert_ptr->convert_init(lon0, lat0, alt0);

        flag = false;
    }

    float arr0[3], arr1[3], arr2[3];
    float* enu0 = convert_ptr->lla2enu(rtk0);
    arr0[0] = enu0[0];
    arr0[1] = enu0[1];
    arr0[2] = enu0[2];
    float* enu1 = convert_ptr->lla2enu(rtk1);
    arr1[0] = enu1[0];
    arr1[1] = enu1[1];
    arr1[2] = enu1[2];
    float* enu2 = convert_ptr->lla2enu(rtk2);
    arr2[0] = enu1[0];
    arr2[1] = enu1[1];
    arr2[2] = enu1[2];

    pub_msgs(arr0,arr1,arr2);
}


int main(int argc, char **argv)
{
    ros::init(argc,argv,"init_pose");
    ros::NodeHandle nh;

    message_filters::Subscriber<sensor_msgs::NavSatFix> gps0_sub(nh, "/jackal0/gps/fix", 1);
    message_filters::Subscriber<sensor_msgs::NavSatFix> gps1_sub(nh, "/jackal1/gps/fix", 1);
    message_filters::Subscriber<sensor_msgs::NavSatFix> gps2_sub(nh, "/jackal2/gps/fix", 1);
    pose_pub = nh.advertise<enu_msgs::multi_enus>("enu_data", 1);
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::NavSatFix, sensor_msgs::NavSatFix, sensor_msgs::NavSatFix> MySyncPolicy;  //ExactTime ApproximateTime
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(3), gps0_sub, gps1_sub, gps2_sub);
    sync.registerCallback(boost::bind(&callback, _1, _2, _3));

    ROS_INFO("ROS start!");

    ros::spin();

    if (!ros::ok())
    {
        ROS_INFO("ROS is not running!");
        delete convert_ptr;
        convert_ptr = nullptr;
    }

    return 0;
}