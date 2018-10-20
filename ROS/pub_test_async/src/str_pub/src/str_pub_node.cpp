#include <ros/ros.h>
#include <unistd.h>
#include <std_msgs/String.h>
#include <ioniq_msgs/cluster.h>

int main(int argc, char** argv){

		ros::init(argc,argv,"cluster_pub");
		ros::NodeHandle	nh;
		
		ros::Publisher pub_msg = nh.advertise<ioniq_msgs::cluster>("/cluster_raw", 1);
		
		ros::Rate loop_rate(1);
		
		int count = 0;
		
		while(ros::ok()){
		
			ioniq_msgs::cluster cluster;
			
			std::stringstream ss;
			ss << "hello world" << count;
			cluster.gear = ss.str();
			cluster.speed = count;
			
			pub_msg.publish(cluster);

			ros::spinOnce();
			
			count++;
			loop_rate.sleep();
		}
}
