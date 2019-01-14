#include <string>

#include <ros/console.h>

#include <x264.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>

#include <liveMedia/liveMedia.hh>
#include <BasicUsageEnvironment/BasicUsageEnvironment.hh>
#include <groupsock/GroupsockHelper.hh>

class RTP
{
// RTP Varialble
public:
  RTP();
  ~RTP();

private:
  UsageEnvironment *env;
  char const *inputFileName = "test.264";
  H264VideoStreamFramer *videoSource;
  RTPSink *videoSink;
  RTCPInstance *rtcp;

  TaskScheduler *scheduler;
  struct in_addr destinationAddress;

  Groupsock rtpGroupsock;
  Groupsock rtcpGroupsock

  Port rtpPort;
  Port rtcpPort;

  void initial();
  void play(); // forward
  void afterPlaying();

// x264 Varialble
public:
    X264Encoder();
    ~X264Encoder();
    bool open(std::string filename, bool datapath); /* open for encoding */
    bool encode(char *pixels);                      /* encode the given data */
    bool close();                                   /* close the encoder and file, frees all memory */
  private:
    bool validateSettings(); /* validates if all params are set correctly, like width,height, etc.. */
    void setParams();        /* sets the x264 params */

    /* params the user should set */
    int in_width;
    int in_height;
    int out_width;
    int out_height;
    int fps; /* e.g. 25, 60, etc.. */
    AVPixelFormat in_pixel_format;
    AVPixelFormat out_pixel_format;

    /* x264 */
    AVPicture pic_raw; /* used for our "raw" input container */
    x264_picture_t pic_in;
    x264_picture_t pic_out;
    x264_param_t params;
    x264_nal_t *nals;
    x264_t *encoder;
    int num_nals;

    /* input / output */
    int pts;
    struct SwsContext *sws;
    FILE *fp;
}

RTP::RTP(){
}

RTP::~RTP(){
}

void RTP::RTP(){
  // TaskScheduler *scheduler = BasicTaskScheduler::createNew();
  // env = BasicUsageEnvironment::createNew(*scheduler);

  // // Create 'groupsocks' for RTP and RTCP:
  // struct in_addr destinationAddress;
  // destinationAddress.s_addr = chooseRandomIPv4SSMAddress(*env);
  // // Note: This is a multicast address.  If you wish instead to stream
  // // using unicast, then you should use the "testOnDemandRTSPServer"
  // // test program - not this test program - as a model.

  // const unsigned short rtpPortNum = 18888;
  // const unsigned short rtcpPortNum = rtpPortNum + 1;
  // const unsigned char ttl = 255;

  // const Port rtpPort(rtpPortNum);
  // const Port rtcpPort(rtcpPortNum);

  // Groupsock rtpGroupsock(*env, destinationAddress, rtpPort, ttl);
  // rtpGroupsock.multicastSendOnly(); // we're a SSM source
  // Groupsock rtcpGroupsock(*env, destinationAddress, rtcpPort, ttl);
  // rtcpGroupsock.multicastSendOnly(); // we're a SSM source

  // // Create a 'H264 Video RTP' sink from the RTP 'groupsock':
  // OutPacketBuffer::maxSize = 100000;
  // videoSink = H264VideoRTPSink::createNew(*env, &rtpGroupsock, 96);

  // // Create (and start) a 'RTCP instance' for this RTP sink:
  // const unsigned estimatedSessionBandwidth = 500; // in kbps; for RTCP b/w share
  // const unsigned maxCNAMElen = 100;
  // unsigned char CNAME[maxCNAMElen + 1];
  // gethostname((char *)CNAME, maxCNAMElen);
  // CNAME[maxCNAMElen] = '\0'; // just in case
  // RTCPInstance *rtcp = RTCPInstance::createNew(*env, &rtcpGroupsock,
  //                                              estimatedSessionBandwidth, CNAME,
  //                                              videoSink, NULL /* we're a server */,
  //                                              True /* we're a SSM source */);
  // // Note: This starts RTCP running automatically

  // Start the streaming:
  // *env << "Beginning streaming...\n";
  // play();

  // env->taskScheduler().doEventLoop(); // does not return
}

void RTP::afterPlaying(void * /*clientData*/){
  *env << "...done reading from file\n";
  videoSink->stopPlaying();
  Medium::close(videoSource);
  // Note that this also closes the input file that this source read from.

  // Start playing once again:
  play();
}

void RTP::play(){
  // Open the input file as a 'byte-stream file source':
  ByteStreamFileSource *fileSource = ByteStreamFileSource::createNew(*env, inputFileName);
  if (fileSource == NULL){
    *env << "Unable to open file \"" << inputFileName
         << "\" as a byte-stream file source\n";
    exit(1);
  }

  FramedSource *videoES = fileSource;

  // Create a framer for the Video Elementary Stream:
  videoSource = H264VideoStreamFramer::createNew(*env, videoES);

  // Finally, start playing:
  *env << "Beginning to read from file...\n";
  videoSink->startPlaying(*videoSource, afterPlaying, videoSink);
}