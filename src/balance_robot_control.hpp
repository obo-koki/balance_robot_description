#include <ros/ros.h>
#include <stdio.h>
#include <chrono>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <iostream>
#include <mutex>
//#include "imu.h"

class BalanceRobotControl{
    protected:

        // Timer callback debug
        ros::WallTime pre_time;
        ros::WallTime time; 
        std::mutex m;

        //ros
        ros::NodeHandle node_handle_;
        ros::Publisher vel_pub_;
        ros::Subscriber imu_sub_;
        void imu_callback(const sensor_msgs::Imu::ConstPtr&);
        ros::WallTimer process_timer_;
        void timer_callback(const ros::WallTimerEvent&);

        //Other
        void vel_control();
        double robot_pitch;
    public:
        BalanceRobotControl(ros::NodeHandle);
        virtual void vel_stop();
        void main_loop();
};
