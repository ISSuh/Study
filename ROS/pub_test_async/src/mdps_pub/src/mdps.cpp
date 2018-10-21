#include <ros/ros.h>
#include <unistd.h>
#include <ioniq_msgs/mdps.h>

int main(int argc, char** argv){

		ros::init(argc,argv,"mdps_pub");
		ros::NodeHandle	nh;
		
		ros::Publisher pub = nh.advertise<ioniq_msgs::mdps>("/can/mdps", 100);
		
		ros::Rate loop_rate(1);
		
		float count = 0;
		uint32_t seq = 0;
		ros::Time time;
		std::stringstream id;
		id << "mdps";

		
		while(ros::ok()){	
			ioniq_msgs::mdps mdps;
			
			mdps.header.frame_id = id.str();
			mdps.header.seq = seq;
			mdps.header.stamp = time.now();
			mdps.angle = count;
			mdps.torq = count;
			
			pub.publish(mdps);
			
			ros::spinOnce();
			
			seq++;
			count++;

			loop_rate.sleep();
		}
}
