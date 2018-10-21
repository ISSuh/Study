#include <ros/ros.h>
#include <unistd.h>
#include <ioniq_msgs/whl_spd.h>

int main(int argc, char** argv){

		ros::init(argc,argv,"whlspd_pub");
		ros::NodeHandle	nh;
		
		ros::Publisher pub = nh.advertise<ioniq_msgs::whl_spd>("/can/whl_spd", 100);
		
		ros::Rate loop_rate(1);
		
		double count = 0;
        uint32_t seq = 0;
		ros::Time time;
        std::stringstream id;
		id << "whl_spd";

		
		while(ros::ok()){	
			ioniq_msgs::whl_spd whl_spd;
			
            whl_spd.header.frame_id = id.str();
			whl_spd.header.seq = seq;
			whl_spd.header.stamp = time.now();
			whl_spd.whl_spd_fl = count;
			whl_spd.whl_spd_fr = count;
            whl_spd.whl_spd_rl = count;
            whl_spd.whl_spd_rr = count;
			
			pub.publish(whl_spd);
			
			ros::spinOnce();
			
			seq++;
            count++;
			loop_rate.sleep();
		}
}
