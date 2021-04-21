#include "balance_robot_control.hpp"

BalanceRobotControl::BalanceRobotControl(ros::NodeHandle nh){

    //ROS
    node_handle_ = nh;
    imu_sub_ = nh.subscribe("/imu/data", 10, &BalanceRobotControl::imu_callback, this);
    //process_timer_ = nh.createWallTimer(ros::WallDuration(0.001),&BalanceRobotControl::timer_callback,this);
    vel_pub_ = nh.advertise<geometry_msgs::Twist>("balance_robot/diff_drive_controller/cmd_vel",5);

    //Timer callback debug
    pre_time = ros::WallTime::now();
}

void BalanceRobotControl::imu_callback(const sensor_msgs::Imu::ConstPtr &imu){
    //calculate robot pitch
    robot_pitch = atan(-imu->linear_acceleration.x/(sqrt(pow(imu->linear_acceleration.y,2)+pow(imu->linear_acceleration.z,2))));
}

void BalanceRobotControl::timer_callback(const ros::WallTimerEvent &e){
    vel_control();
}

void BalanceRobotControl::vel_stop(){
    geometry_msgs::Twist vel;
    vel_pub_.publish(vel);
}

void BalanceRobotControl::vel_control(){
    geometry_msgs::Twist vel;
    if (robot_pitch > 0){
        vel.linear.x = -1.0;
    }else if( robot_pitch < 0){
        vel.linear.x = 1.0;
    }else{
        vel.linear.x =0.0;
    }
    vel_pub_.publish(vel);
    }

void BalanceRobotControl::main_loop(){
    //Motor start
    ros::Rate rate(5);
    while (ros::ok()){
        vel_control();
        rate.sleep();
    }
    vel_stop();
}