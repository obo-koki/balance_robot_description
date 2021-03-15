#include "balance_robot_control.hpp"

BalanceRobotControl::BalanceRobotControl(ros::NodeHandle nh, ros::NodeHandle pnh){

    //ROS
    node_handle_ = nh;
    private_node_handle_ = pnh;
    
    imu_sub_ = nh.subscribe("/imu/data", 10, &BalanceRobotControl::imu_callback, this);
    vel_sub_ = nh.subscribe("/target_cmd_vel", 10, &BalanceRobotControl::vel_callback, this);
    wheel_sub_ = nh.subscribe("/balance_robot/diff_drive_controller_effort/wheel_joint_controller_state", 10, 
        &BalanceRobotControl::wheel_callback, this);
    //process_timer_ = nh.createWallTimer(ros::WallDuration(0.001),&BalanceRobotControl::timer_callback,this);
    torque_pub_ = nh.advertise<std_msgs::Float32MultiArray>("balance_robot/diff_drive_controller_effort/cmd_torque",5);
    state_pub_ = nh.advertise<std_msgs::Float32>("balance_robot_control/robot_state",5);
    show_torque_pub_ = nh.advertise<std_msgs::Float32>("balance_robot_control/torque_state",5);

    pnh.getParam("control_gain", control_gain_);
    pnh.getParam("wheel_radius", wheel_radius_);
    pnh.getParam("torque_const", torque_const_);
    pnh.getParam("motor_resist", motor_resist_);

    //Dynamic param
    callback_ = boost::bind(&BalanceRobotControl::param_callback, this, _1, _2);
    param_server_.setCallback(callback_);
    gain_theta_ = control_gain_.at(0);
    gain_omega_ = control_gain_.at(1);
    gain_fai_ = control_gain_.at(2);
    gain_error_ = control_gain_.at(3);

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

void BalanceRobotControl::wheel_callback(const control_msgs::JointTrajectoryControllerState::ConstPtr &state){
    //get robot current wheel velocity
    wheel_angle_vel = (state->actual.velocities[0] + state->actual.velocities[1])/2;
}

void BalanceRobotControl::timer_callback(const ros::WallTimerEvent &e){
    vel_control();
}

void BalanceRobotControl::param_callback(const balance_robot_description::gainConfig& config, uint32_t level){
    ROS_INFO("Received dynamic param | gain_theta:%lf,gain_omega:%lf gain_fai:%lf gain_error:%lf",
        config.gain_theta, config.gain_omega, config.gain_fai, config.gain_error);
    
    gain_theta_ = config.gain_theta;
    gain_omega_ = config.gain_omega;
    gain_fai_ = config.gain_fai;
    gain_error_ = config.gain_error;
}

void BalanceRobotControl::vel_control(){
    std_msgs::Float32MultiArray torque_cmd;
    std_msgs::Float32 state;
    std_msgs::Float32 torque;

    float volt;
    torque_cmd.data.resize(2);
    //state.data.resize(4);
    //diff = diff + target_linear_x - linear_x * 1.0/10.0;
    
    ROS_INFO("robot_pitch:%lf, robot_pitch_vel:%lf, wheel_angle_vel:%lf, diff:%lf", 
                robot_pitch, robot_pitch_vel, wheel_angle_vel, diff);

    state.data = robot_pitch;
    //state.data[0] = robot_pitch;
    //state.data[1] = robot_pitch_vel;
    //state.data[2] = wheel_angle_vel;
    //state.data[3] = diff;

    state_pub_.publish(state);

    volt = gain_theta_ * (robot_pitch) 
            +gain_omega_ * (robot_pitch_vel)
            +gain_fai_ * (wheel_angle_vel);
    //        -gain_error_ * diff * 1.0/10.0;
    
    torque.data = volt * torque_const_ / motor_resist_;
    torque_cmd.data[0] = volt * torque_const_ / motor_resist_;
    torque_cmd.data[1] = volt * torque_const_ / motor_resist_;

    show_torque_pub_.publish(torque);

    /*
    robot_pitch_pre = robot_pitch;
    robot_pitch_vel_pre = robot_pitch_vel;
    wheel_angle_vel_pre = wheel_angle_vel;

    vel.angular.z = target_angular_z;
    */

    ROS_INFO("Publish torque_right:%lf, torque_left:%lf", torque_cmd.data[0], torque_cmd.data[1]);
    torque_pub_.publish(torque_cmd);
    }

void BalanceRobotControl::vel_stop(){
    geometry_msgs::Twist vel;
    torque_pub_.publish(vel);
}

void BalanceRobotControl::main_loop(){
    //Motor start
    ros::Rate rate(100);
    while (ros::ok()){
        vel_control();
        ros::spinOnce();
        rate.sleep();
    }
    vel_stop();
}