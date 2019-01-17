#include "ros/ros.h"
#include "sensor_msgs/Image.h"

#include "Encode.cpp"

X264Encoder enc;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void imageCallback(const sensor_msgs::Image::ConstPtr& msg){
  ROS_INFO("%d x %d", msg->width, msg->height);
  enc.encode(&(msg->data[0]));
}

int main(int argc, char **argv){
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/image_raw", 1000, imageCallback);

  enc.open();


  ros::spin();

  return 0;
}