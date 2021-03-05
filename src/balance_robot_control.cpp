#include "balance_robot_control.hpp"

BalanceRobotControl::BalanceRobotControl(ros::NodeHandle nh, ros::NodeHandle pnh){

    //ROS
    node_handle_ = nh;
    private_node_handle_ = pnh;
    
    imu_sub_ = nh.subscribe("/imu/data", 10, &BalanceRobotControl::imu_callback, this);
    vel_sub_ = nh.subscribe("/target_cmd_vel", 10, &BalanceRobotControl::vel_callback, this);
    vel_sub_feedback_ = nh.subscribe("/balance_robot/diff_drive_controller/cmd_vel_out", 10, 
        &BalanceRobotControl::vel_feedback_callback, this);
    //process_timer_ = nh.createWallTimer(ros::WallDuration(0.001),&BalanceRobotControl::timer_callback,this);
    vel_pub_ = nh.advertise<geometry_msgs::Twist>("balance_robot/diff_drive_controller/cmd_vel",5);

    pnh.getParam("control_gain", control_gain);
    pnh.getParam("wheel_radius", wheel_radius);

    //Timer callback debug
    pre_time = ros::WallTime::now();

    //Initialize
    robot_pitch = 0;
    robot_pitch_pre = 0;
    robot_pitch_vel = 0;
    robot_pitch_vel_pre = 0;
    linear_x = 0;
    target_linear_x = 0;
}

void BalanceRobotControl::imu_callback(const sensor_msgs::Imu::ConstPtr &imu){
    //calculate robot pitch
    robot_pitch = atan(-imu->linear_acceleration.x/(sqrt(pow(imu->linear_acceleration.y,2)+pow(imu->linear_acceleration.z,2))));
    robot_pitch_vel = imu->angular_velocity.y;
}

void BalanceRobotControl::vel_callback(const geometry_msgs::Twist::ConstPtr &vel){
    //get target velocity
    target_linear_x = vel->linear.x;
    target_angular_z = vel->angular.z;
}

void BalanceRobotControl::vel_feedback_callback(const geometry_msgs::TwistStamped::ConstPtr &vel){
    //get robot current velocity
    linear_x = vel->twist.linear.x;
    wheel_angle_vel = linear_x / wheel_radius - robot_pitch_vel;
}

void BalanceRobotControl::timer_callback(const ros::WallTimerEvent &e){
    vel_control();
}

void BalanceRobotControl::vel_control(){
    geometry_msgs::Twist vel;
    diff = diff + target_linear_x - linear_x * 1.0/10.0;
    
    ROS_INFO("robot_pitch:%lf, robot_pitch_vel:%lf, wheel_angle_vel:%lf, diff:%lf", 
                robot_pitch, robot_pitch_vel, wheel_angle_vel, diff);
    vel.linear.x = control_gain.at(0) * (robot_pitch) 
                  +control_gain.at(1) * (robot_pitch_vel)
                  +control_gain.at(2) * (wheel_angle_vel)
                  -control_gain.at(3) * diff * 1.0/10.0;
    
    robot_pitch_pre = robot_pitch;
    robot_pitch_vel_pre = robot_pitch_vel;
    wheel_angle_vel_pre = wheel_angle_vel;

    vel.angular.z = target_angular_z;

    ROS_INFO("Publish vx:%lf, az:%lf", vel.linear.x, vel.angular.z);
    vel_pub_.publish(vel);
    }

void BalanceRobotControl::vel_stop(){
    geometry_msgs::Twist vel;
    vel_pub_.publish(vel);
}

void BalanceRobotControl::main_loop(){
    //Motor start
    ros::Rate rate(10);
    while (ros::ok()){
        vel_control();
        ros::spinOnce();
        rate.sleep();
    }
    vel_stop();
}