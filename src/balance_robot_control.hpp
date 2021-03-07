#include <ros/ros.h>
#include <stdio.h>
#include <chrono>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <control_msgs/JointTrajectoryControllerState.h>
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

        ros::Publisher torque_pub_;

        ros::Subscriber imu_sub_;
        void imu_callback(const sensor_msgs::Imu::ConstPtr&);

        ros::Subscriber vel_sub_;
        void vel_callback(const geometry_msgs::Twist::ConstPtr&);

        ros::Subscriber wheel_sub_;
        void wheel_callback(const control_msgs::JointTrajectoryControllerState::ConstPtr&);

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
        std::vector<double> control_gain_;
        double wheel_radius_;
        double torque_const_;
        double motor_resist_;

    public:
        BalanceRobotControl(ros::NodeHandle, ros::NodeHandle);
        virtual void vel_stop();
        void main_loop();
};
