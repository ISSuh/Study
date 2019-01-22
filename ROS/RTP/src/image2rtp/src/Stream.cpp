#include <string>

#include <ros/console.h>

extern "C"{
#include <x264.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
}

#include <liveMedia/liveMedia.hh>
#include <BasicUsageEnvironment/BasicUsageEnvironment.hh>
#include <groupsock/GroupsockHelper.hh>

class RTP{
// RTP Varialble
public:
  RTP();
  ~RTP();

private:
  UsageEnvironment *env;
  H264VideoStreamFramer *videoSource;
  RTPSink *videoSink;
  RTCPInstance *rtcp;

  TaskScheduler *scheduler;
  struct in_addr destinationAddress;

  void initial();
  void play(const uint8_t *pixels); // forward
  void afterPlaying(void *);
};

RTP::RTP(){
}

RTP::~RTP(){
}

void RTP::initial(){
  scheduler = BasicTaskScheduler::createNew();
  env = BasicUsageEnvironment::createNew(*scheduler);

  // Create 'groupsocks' for RTP and RTCP:
  destinationAddress.s_addr = chooseRandomIPv4SSMAddress(*env);
  // Note: This is a multicast address.  If you wish instead to stream
  // using unicast, then you should use the "testOnDemandRTSPServer"
  // test program - not this test program - as a model.

  const unsigned short rtpPortNum = 18888;
  const unsigned short rtcpPortNum = rtpPortNum + 1;
  const unsigned char ttl = 255;

  const Port rtpPort(rtpPortNum);
  const Port rtcpPort(rtcpPortNum);

  Groupsock rtpGroupsock(*env, destinationAddress, rtpPort, ttl);
  rtpGroupsock.multicastSendOnly(); // we're a SSM source
  Groupsock rtcpGroupsock(*env, destinationAddress, rtcpPort, ttl);
  rtcpGroupsock.multicastSendOnly(); // we're a SSM source

  // Create a 'H264 Video RTP' sink from the RTP 'groupsock':
  OutPacketBuffer::maxSize = 100000;
  videoSink = H264VideoRTPSink::createNew(*env, &rtpGroupsock, 96);

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
  *env << "Beginning streaming...\n";
  // play();

  env->taskScheduler().doEventLoop(); // does not return
}

void RTP::afterPlaying(void * /*clientData*/){
  *env << "...done reading from file\n";
  videoSink->stopPlaying();
  Medium::close(videoSource);
  // Note that this also closes the input file that this source read from.

  // Start playing once again:
  // play();
}

void RTP::play(const uint8_t *pixels){
  // Open the input file as a 'byte-stream file source':
  // ByteStreamFileSource *fileSource = ByteStreamFileSource::createNew(*env, inputFileName);
  ByteStreamMemoryBufferSource *imageSource = ByteStreamMemoryBufferSource(&env,pixels,);


  FramedSource *videoES = imageSource;

  // Create a framer for the Video Elementary Stream:
  videoSource = H264VideoStreamFramer::createNew(*env, videoES);

  // Finally, start playing:
  *env << "Beginning to read from file...\n";
  videoSink->startPlaying(*videoSource, afterPlaying, videoSink);
}