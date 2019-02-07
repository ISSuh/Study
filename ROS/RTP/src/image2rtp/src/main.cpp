#include <signal.h>
#include <iostream>

#include "ros/ros.h"
#include "sensor_msgs/Image.h"

#include "RTP.cpp"
#include <liveMedia/liveMedia.hh>
#include <BasicUsageEnvironment/BasicUsageEnvironment.hh>
#include <groupsock/GroupsockHelper.hh>
#include "MyTaskScheduler.cpp"

H264SourceRTP *rosSource;
char watch = 0;

void my_handler(int s){
  ROS_INFO("Caught signal %d\n",s);
  std::cout << "Caught signal" << std::endl;
  watch = 1;

  exit(1);
}

void imageCallback(const sensor_msgs::Image::ConstPtr& msg){
  ROS_INFO("------------------------------");
  ROS_INFO("%d x %d", msg->width, msg->height);

  rosSource->encodeNewFrame(&(msg->data[0]));
}

int main(int argc, char **argv){
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = my_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/image_raw", 1000, imageCallback);

  UsageEnvironment *env;

  H264VideoStreamFramer* videoSource;
  RTPSink *videoSink;
  RTCPInstance *rtcp;

  TaskScheduler *scheduler;
  struct in_addr destinationAddress;

  scheduler = MyTaskScheduler::createNew();
  env = BasicUsageEnvironment::createNew(*scheduler);

  // Create 'groupsocks' for RTP and RTCP:
  
  char const* outputAddressStr = "127.0.0.1";
  const unsigned short rtpPortNum = 18888;
  const unsigned short rtcpPortNum = rtpPortNum + 1;
  const unsigned char ttl = 255;

  destinationAddress.s_addr = chooseRandomIPv4SSMAddress(*env);
  const Port rtpPort(rtpPortNum);
  const Port rtcpPort(rtcpPortNum);

  Groupsock rtpGroupsock(*env, destinationAddress, rtpPort, ttl);
  rtpGroupsock.multicastSendOnly(); // we're a SSM source
  Groupsock rtcpGroupsock(*env, destinationAddress, rtcpPort, ttl);
  rtcpGroupsock.multicastSendOnly(); // we're a SSM source

  // Create a 'H264 Video RTP' sink from the RTP 'groupsock':
  OutPacketBuffer::maxSize = 100000;
  videoSink = H264VideoRTPSink::createNew(*env, &rtpGroupsock, 103);

  // Create (and start) a 'RTCP instance' for this RTP sink:
  const unsigned estimatedSessionBandwidth = 500; // in kbps; for RTCP b/w share
  const unsigned maxCNAMElen = 100;
  unsigned char CNAME[maxCNAMElen + 1];
  gethostname((char *)CNAME, maxCNAMElen);
  CNAME[maxCNAMElen] = '\0'; // just in case
  rtcp = RTCPInstance::createNew(*env, &rtcpGroupsock,
                                               estimatedSessionBandwidth, CNAME,
                                               videoSink, NULL /* we're a server */,
                                               True /* we're a SSM source */);
  // Note: This starts RTCP running automatically

  // Start the streaming:
  ROS_INFO("Beginning streaming");
  
  rosSource = H264SourceRTP::createNew(*env);
  rosSource->openX264Encord(960, 604, 17, AV_PIX_FMT_RGB24, AV_PIX_FMT_YUV420P);

  videoSource = H264VideoStreamFramer::createNew(*env, rosSource, false);

  // Finally, start playing:
  ROS_INFO("Beginning to read from ROS Image...\n");
  
  videoSink->startPlaying(*videoSource, NULL, videoSink);
  
  // ros::spin();
  env->taskScheduler().doEventLoop(&watch);
  
  ros::shutdown();
  return 0;
}
