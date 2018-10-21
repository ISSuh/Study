#include <ros/ros.h>
#include <unistd.h>
#include <ioniq_msgs/accel.h>

int main(int argc, char** argv){

		ros::init(argc,argv,"accel_pub");
		ros::NodeHandle	nh;
		
		ros::Publisher pub = nh.advertise<ioniq_msgs::accel>("/can/accel", 100);
		
		ros::Rate loop_rate(1);
		
		float count = 0;
        uint32_t seq = 0;
		ros::Time time;
        std::stringstream id;
		id << "accel";

		
		while(ros::ok()){	
			ioniq_msgs::accel accel;
			
            accel.header.frame_id = id.str();
			accel.header.seq = seq;
			accel.header.stamp = time.now();
			accel.lat_accel = count;
			accel.long_accel = count;
            accel.yaw_rate = count;
			
			pub.publish(accel);
			
			ros::spinOnce();
			
			seq++;
            count++;
			loop_rate.sleep();
		}
}
