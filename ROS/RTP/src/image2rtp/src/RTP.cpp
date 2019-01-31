#ifndef H264_RTP_STREAM
#define H264_RTP_STREAM

#include <queue>
#include <liveMedia/liveMedia.hh>
#include <BasicUsageEnvironment/BasicUsageEnvironment.hh>
#include <groupsock/GroupsockHelper.hh>

#include "Encoder.cpp"

#include "sensor_msgs/Image.h"


class H264SourceRTP : public FramedSource{
public:
    static LiveSourceWithx264* createNew(UsageEnvironment& env);
    static EventTriggerId eventTriggerId;
    std::queue<sensor_msgs::Image> InImage;

protected:
    LiveSourceWithx264(UsageEnvironment& env);
    virtual ~LiveSourceWithx264(void);
private:
    virtual void doGetNextFrame();
    static void deliverFrame0(void* clientData);
    void deliverFrame();
    void encodeNewFrame();
    static unsigned referenceCount;
    timeval currentTime;
    // Remember the x264 encoder wrapper we wrote in the start
    X264Encoder *encoder;
}; 

EventTriggerId H264SourceRTP::eventTriggerId = 0;

unsigned H264SourceRTP::referenceCount = 0;

LiveSourceWithx264* H264SourceRTP::createNew(UsageEnvironment& env){
    return new H264SourceRTP(env);
}


H264SourceRTP::H264SourceRTP(UsageEnvironment& env) : FramedSource(env){
    if(referenceCount == 0)
    {

    }
    ++referenceCount;
    
    encoder = new x264Encoder();
    encoder->open(960, 604, 30, AV_PIX_FMT_RGB24, AV_PIX_FMT_YUV420P);
    
    if(eventTriggerId == 0)
    {
        eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
    }
}


H264SourceRTP::~H264SourceRTP(void)
{
    --referenceCount;
    encoder->close();
    envir().taskScheduler().deleteEventTrigger(eventTriggerId);
    eventTriggerId = 0;
}

void H264SourceRTP::encodeNewFrame()
{
        rawImage.data = NULL;
        while(rawImage.data == NULL)
        {
            videoCaptureDevice >> rawImage;
            cv::waitKey(100);
        }
        // Got new image to stream
        assert(rawImage.data != NULL);
        encoder->encodeFrame(rawImage);
        // Take all nals from encoder output queue to our input queue
        while(encoder->isNalsAvailableInOutputQueue() == true)
        {
            x264_nal_t nal = encoder->getNalUnit();
            nalQueue.push(nal);
        }
}

void H264SourceRTP::deliverFrame0(void* clientData)
{
    ((H264SourceRTP*)clientData)->deliverFrame();
}

void H264SourceRTP::doGetNextFrame()
{
    if(nalQueue.empty() == true)
    {
        encodeNewFrame();
        gettimeofday(&currentTime,NULL);
        deliverFrame();
    }
    else
    {
        deliverFrame();
    }
}

void H264SourceRTP::deliverFrame()
{
    if(!isCurrentlyAwaitingData()) return;
    x264_nal_t nal = nalQueue.front();
    nalQueue.pop();
    assert(nal.p_payload != NULL);
    // You need to remove the start code which is there in front of every nal unit.  
    // the start code might be 0x00000001 or 0x000001. so detect it and remove it. pass remaining data to live555    
    int trancate = 0;
    if (nal.i_payload >= 4 && nal.p_payload[0] == 0 && nal.p_payload[1] == 0 && nal.p_payload[2] == 0 && nal.p_payload[3] == 1 )
    {
        trancate = 4;
    }
    else
    {
        if(nal.i_payload >= 3 && nal.p_payload[0] == 0 && nal.p_payload[1] == 0 && nal.p_payload[2] == 1 )
        {
            trancate = 3;
        }
    }

    if(nal.i_payload-trancate > fMaxSize)
    {
        fFrameSize = fMaxSize;
        fNumTruncatedBytes = nal.i_payload-trancate - fMaxSize;
    }
    else
    {
        fFrameSize = nal.i_payload-trancate;
    }
    fPresentationTime = currentTime;
    memmove(fTo,nal.p_payload+trancate,fFrameSize);
    FramedSource::afterGetting(this);
}  


#endif