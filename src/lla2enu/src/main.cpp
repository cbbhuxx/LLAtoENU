//
// Created by cbbhuxx on 23-8-17.
//

#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/NavSatFix.h>
#include <../include/converter.h>
#include <../include/assistor.h>


bool flag = true;   // 坐标系起点初始化标志位
converter* convert_ptr = new converter();
assistor* assist_ptr = new assistor("enu_data");

void callback(const sensor_msgs::NavSatFixConstPtr& gps0, const sensor_msgs::NavSatFixConstPtr& gps1, const sensor_msgs::NavSatFixConstPtr& gps2)
{
    sensor_msgs::NavSatFix rtk0, rtk1, rtk2;
    rtk0 = *gps0;
    rtk1 = *gps1;
    rtk2 = *gps2;
    if (flag)
    {
        float lon0, lat0, alt0;  //机器人0起始经纬高
        lon0 = rtk0.longitude;
        lat0 = rtk1.latitude;
        alt0 = rtk2.altitude;
        convert_ptr->convert_init(lon0, lat0, alt0);

        flag = false;
    }

    float* enu0 = convert_ptr->lla2enu(rtk0);
    float* enu1 = convert_ptr->lla2enu(rtk1);
    float* enu2 = convert_ptr->lla2enu(rtk2);


    assist_ptr->pub_msgs(enu0,enu1,enu2);

}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"init_pose");
    ros::NodeHandle nh;

    message_filters::Subscriber<sensor_msgs::NavSatFix> gps0_sub(nh, "gps0", 1);
    message_filters::Subscriber<sensor_msgs::NavSatFix> gps1_sub(nh, "gps1", 1);
    message_filters::Subscriber<sensor_msgs::NavSatFix> gps2_sub(nh, "gps2", 1);

    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::NavSatFix,
            sensor_msgs::NavSatFix,
            sensor_msgs::NavSatFix> MySyncPolicy;
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(3), gps0_sub, gps1_sub, gps2_sub);
    sync.registerCallback(boost::bind(&callback, _1, _2, _3));

    if (!ros::ok())
    {
        ROS_INFO("ROS is not running!");
        delete convert_ptr,assist_ptr;
        convert_ptr = nullptr;
        assist_ptr = nullptr;
    }

    ros::spin();

    return 0;

}