#include "ros/ros.h"
#include <std_msgs/Empty.h>
#include <dbw_polaris_msgs/GearCmd.h>
#include "geometry_msgs/Twist.h"

#define VEL_PUB_NAME "/vehicle/cmd_vel"

int main(int argc, char **argv){
    ros::init(argc, argv, "Turn_Node");

    ros::NodeHandle nh;

    ros::Publisher velPub = nh.advertise<geometry_msgs::Twist>(VEL_PUB_NAME, 1);
    ros::Publisher enablePub = nh.advertise<std_msgs::Empty>("/vehicle/enable", 1);
    ros::Publisher gearPub = nh.advertise<dbw_polaris_msgs::GearCmd>("/vehicle/gear_cmd", 1);

    dbw_polaris_msgs::GearCmd gear_msg;

    ROS_INFO_STREAM("turn node started");

    geometry_msgs::Twist cmd;

    ros::Duration(2).sleep();

    ROS_INFO_STREAM("Set Forward");
    gear_msg.cmd.gear = dbw_polaris_msgs::Gear::DRIVE;
    gearPub.publish(gear_msg);
    cmd.linear.x = .75;
    enablePub.publish(std_msgs::Empty());

    ros::Duration(.4).sleep();
    ROS_INFO_STREAM("Go Forward");

    double secs = ros::Time::now().toSec();

    while (ros::Time::now().toSec() - secs < 3){
        velPub.publish(cmd);
        ros::Duration(.05).sleep();
    }

    ROS_INFO_STREAM("STOP");
    cmd.linear.x = 0;
    velPub.publish(cmd);

}