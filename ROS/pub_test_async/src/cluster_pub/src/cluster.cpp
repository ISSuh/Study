#include <ros/ros.h>
#include <unistd.h>
#include <std_msgs/String.h>
#include <ioniq_msgs/cluster.h>

int main(int argc, char** argv){

		ros::init(argc,argv,"cluster_pub");
		ros::NodeHandle	nh;
		
		ros::Publisher pub = nh.advertise<ioniq_msgs::cluster>("/can/cluster", 100);
		
		ros::Rate loop_rate(1);
		
		uint8_t count = 60;
		uint32_t seq = 0;
		ros::Time time;
		std::stringstream id;
		id << "cluster";

		std::stringstream ss;
		ss << "LV1";

		while(ros::ok()){
			ioniq_msgs::cluster cluster;
			
			cluster.header.frame_id = id.str();
			cluster.header.seq = seq;
			cluster.header.stamp = time.now();
			cluster.gear = ss.str();
			cluster.speed = count;
			
			pub.publish(cluster);

			ros::spinOnce();
			
			seq++;
			loop_rate.sleep();
		}
}
