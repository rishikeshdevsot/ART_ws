#include <ros/ros.h>
#include "tf/tf.h"
#include "tf/transform_broadcaster.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Quaternion.h"

nav_msgs::Odometry odom;

void odomcb(const nav_msgs::Odometry& msg)
{
  odom = msg;  
}

int main(int argc, char** argv){
  ros::init(argc, argv, "base_zed_tf");
  ros::NodeHandle n;

  ros::Time current_time,prev_time;
  current_time = ros::Time::now();

  geometry_msgs::TransformStamped odom_trans;
  geometry_msgs::Quaternion odom_quat;
  tf::TransformBroadcaster odom_broadcaster;

  ros::Rate r(100);

  ros::Subscriber sub1 = n.subscribe("/odom", 1, odomcb);
 
  while(n.ok()){

    ros::spinOnce();
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "zed_center";

    odom_trans.transform.translation.x = 1*odom.pose.pose.position.x;
    odom_trans.transform.translation.y = 1*odom.pose.pose.position.y;
    odom_trans.transform.translation.z = 0.0;
    odom_quat = tf::createQuaternionMsgFromYaw(1*odom.pose.pose.orientation.z); //orientation quat
    odom_trans.transform.rotation = odom_quat;

    odom_broadcaster.sendTransform(odom_trans);
    r.sleep();

  }
}
