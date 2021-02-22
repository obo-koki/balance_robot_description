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
        ros::NodeHandle private_node_handle_;

        ros::Publisher vel_pub_;
        ros::Subscriber imu_sub_;
        void imu_callback(const sensor_msgs::Imu::ConstPtr&);

        ros::Subscriber vel_sub_;
        void vel_callback(const geometry_msgs::Twist::ConstPtr&);
        ros::Subscriber vel_sub_feedback_;
        void vel_feedback_callback(const geometry_msgs::TwistStamped::ConstPtr&);

        ros::WallTimer process_timer_;
        void timer_callback(const ros::WallTimerEvent&);

        //Other
        void vel_control();
        double robot_pitch;
        double robot_pitch_pre;
        double robot_pitch_vel;
        double robot_pitch_vel_pre;
        double linear_x;
        double target_linear_x;
        double target_angular_z;
        double wheel_angle_vel;
        double wheel_angle_vel_pre;
        double diff;
        double diff_pre;
        std::vector<double> control_gain;
        double wheel_radius;

    public:
        BalanceRobotControl(ros::NodeHandle, ros::NodeHandle);
        virtual void vel_stop();
        void main_loop();
};
