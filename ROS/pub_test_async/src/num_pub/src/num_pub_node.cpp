#include <ros/ros.h>
#include <unistd.h>
#include <std_msgs/Int32.h>
#include <ioniq_msgs/mdps.h>

int main(int argc, char** argv){

		ros::init(argc,argv,"mdps_pub");
		ros::NodeHandle	nh;
		
		ros::Publisher pub_num = nh.advertise<ioniq_msgs::mdps>("/mdps_raw", 1);
		
		ros::Rate loop_rate(1);
		
		float count = 0;
		
		while(ros::ok()){	
			ioniq_msgs::mdps mdps;
			
			mdps.angle = count;
			mdps.torq = count;
			
			pub_num.publish(mdps);
			
			ros::spinOnce();
			
			count++;
			loop_rate.sleep();
		}
}
