#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "tf/tf.h"
#include "tf/transform_broadcaster.h"

double x_n,y_n,z_n,a_n,b_n,c_n =0;
geometry_msgs::Pose curr_pose;

void zedcb(const nav_msgs::Odometry& msg)
{
  double roll, pitch, yaw;
  curr_pose = msg.pose.pose;
  x_n = curr_pose.position.x;
  y_n = curr_pose.position.y;
  z_n = curr_pose.position.z;

  tf::Quaternion q(
    curr_pose.orientation.x,
    curr_pose.orientation.y,
    curr_pose.orientation.z,
    curr_pose.orientation.w);
  tf::Matrix3x3 m(q);
  m.getRPY(roll, pitch, yaw);

  a_n = roll;
  b_n = pitch;
  c_n = yaw;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "odom");
  ros::NodeHandle n;
  ros::Time current_time,prev_time;
  current_time = ros::Time::now();

  ros::Subscriber sub1 = n.subscribe("/zed/odom", 1, zedcb);
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("/odom", 1);
  nav_msgs::Odometry curr_odom;
  tf::TransformBroadcaster odom_broadcaster;
  geometry_msgs::TransformStamped odom_trans;

  ros::Rate loop_rate(10);

  double dt;
  double x,y,z,a,b,c = 0;
  double vx,vy,vz,wx,wy,wz = 0;
  

  while(n.ok())
  { 
    x = x_n;
    y = y_n;
    z = z_n;
    a = a_n;
    b = b_n;
    c = c_n;

    prev_time = current_time; 
    ros::spinOnce(); //check for msgs
    current_time = ros::Time::now();
    dt = (current_time - prev_time).toSec();

    vx = (x_n-x) / dt;
    vy = (y_n-y) / dt;
    vz = (z_n-z) / dt;
    wx = (a_n-a) / dt;
    wy = (b_n-b) / dt;
    wz = (c_n-c) / dt;

    curr_odom.twist.twist.linear.x = vx;
    curr_odom.twist.twist.linear.y = vy;
    curr_odom.twist.twist.linear.z = vz;
    curr_odom.twist.twist.angular.x = wx;
    curr_odom.twist.twist.angular.y = wy;
    curr_odom.twist.twist.angular.z = wz;
    curr_odom.pose.pose = curr_pose;
    curr_odom.header.stamp = current_time; 
    curr_odom.header.frame_id = "odom";
    curr_odom.child_frame_id = "zed_center";

    odom_pub.publish(curr_odom);

    usleep(250000);
    
  }
  return 0;
}

