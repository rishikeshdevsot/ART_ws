#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "base_zed_tf");
  ros::NodeHandle n;

  ros::Rate r(10000);

  tf::TransformBroadcaster broadcaster;
  
  float dx = 0;
  float dy = 0;
  float dz = 0;
  while(n.ok()){
    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(dx, dy, dz)),
        ros::Time::now(),"zed_center", "base_link"));
    r.sleep();
  }
}
