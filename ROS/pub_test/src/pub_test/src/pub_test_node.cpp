#include <ros/ros.h>
#include <unistd.h>
#include <ioniq_msgs/mdps.h>
#include <ioniq_msgs/cluster.h>

int main(int argc, char** argv){

		ros::init(argc,argv,"pub_test");
		ros::NodeHandle	nh;
		
		ros::Publisher pub_msg = nh.advertise<ioniq_msgs::mdps>("/mdps_raw", 1);
		ros::Publisher pub_num = nh.advertise<ioniq_msgs::cluster>("/cluster_raw", 1);
		
		ros::Rate loop_rate(1);
		
		int count = 0;
		float count_f = 0;
		
		while(ros::ok()){
		
			ioniq_msgs::mdps mdps;
			ioniq_msgs::cluster cluster;
			
			std::stringstream ss;
			
			ss << "hello world" << count;
			cluster.gear = ss.str();
			cluster.speed = count;
			
			mdps.angle = count_f;
			mdps.torq = count_f;
			
			pub_msg.publish(mdps);
			pub_num.publish(cluster);
			
			ros::spinOnce();
			
			count++;
			count_f++;
			loop_rate.sleep();
		}
}
