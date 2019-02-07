#ifndef H264_RTP_STREAM
#define H264_RTP_STREAM

#include <queue>
#include <mutex>

extern "C"{
#include <x264.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
}


#include <liveMedia/liveMedia.hh>
#include <BasicUsageEnvironment/BasicUsageEnvironment.hh>
#include <groupsock/GroupsockHelper.hh>

#include "ros/ros.h"

#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

template<typename Data>
class concurrent_queue
{
private:
    mutable boost::mutex the_mutex;
    boost::condition_variable the_condition_variable;
public:
    std::queue<Data> the_queue;
    
    void push(Data const& data)
    {
        boost::mutex::scoped_lock lock(the_mutex);
        the_queue.push(data);
        lock.unlock();
        the_condition_variable.notify_one();
    }

    bool empty() const
    {
        boost::mutex::scoped_lock lock(the_mutex);
        return the_queue.empty();
    }

    bool try_pop(Data& popped_value)
    {
        boost::mutex::scoped_lock lock(the_mutex);
        if(the_queue.empty())
        {
            return false;
        }
        
        popped_value=the_queue.front();
        the_queue.pop();
        return true;
    }

    void wait_and_pop(Data& popped_value)
    {
        boost::mutex::scoped_lock lock(the_mutex);
        while(the_queue.empty())
        {
            the_condition_variable.wait(lock);
        }
        
        popped_value=the_queue.front();
        the_queue.pop();
    }

};

class H264SourceRTP : public FramedSource{
public:
    static H264SourceRTP* createNew(UsageEnvironment& env);
    static EventTriggerId eventTriggerId;
    // std::queue<sensor_msgs::Image> InImage;

    // X264 Encode
    bool openX264Encord(int width_, int height_, int fps_, AVPixelFormat in, AVPixelFormat out);
    bool encodeNewFrame(const uint8_t *pixels);


    H264SourceRTP(UsageEnvironment& env);
    virtual ~H264SourceRTP(void);

private:
    // Live555 
    virtual void doGetNextFrame();
    static void deliverFrame0(void* clientData);
    void deliverFrame();

    // X264 Encode
    void encodeNewFrame();

    static unsigned referenceCount;
    timeval currentTime;

    // Remember the x264 encoder wrapper we wrote in the start
    // X264Encoder *encoder;
    int width;
    int height;
    int fps;
    AVPixelFormat in_pixel_format;
    AVPixelFormat out_pixel_format;

    AVPicture pic_raw; /* used for our "raw" input container */
    x264_picture_t pic_in;
    x264_picture_t pic_out;
    x264_param_t params;
    x264_nal_t *nals;
    x264_t *encoder;
    int num_nals;

    int pts;
    struct SwsContext *sws;

    std::queue<x264_nal_t> Out;
    concurrent_queue<x264_nal_t> Out_;

    
}; 

EventTriggerId H264SourceRTP::eventTriggerId = 0;
unsigned H264SourceRTP::referenceCount = 0;

H264SourceRTP* H264SourceRTP::createNew(UsageEnvironment& env){
    return new H264SourceRTP(env);
}

H264SourceRTP::H264SourceRTP(UsageEnvironment& env) : FramedSource(env){
    if(referenceCount == 0){
    
    }
    ++referenceCount;

    if(eventTriggerId == 0){
        eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
    }
}


H264SourceRTP::~H264SourceRTP(void){
    --referenceCount;
   
   if(!referenceCount){
        envir().taskScheduler().deleteEventTrigger(eventTriggerId);
        eventTriggerId = 0;
   }
}

bool H264SourceRTP::encodeNewFrame(const uint8_t *pixels){
    if (!sws){
        ROS_ERROR("Not initialized, so cannot encode");
        return false;
    }

    // copy the pixels into our "raw input" container.
    if (!avpicture_fill(&pic_raw, pixels, in_pixel_format, width, height)){
        ROS_ERROR("Cannot fill the raw input buffer");
        return false;
    }
    
    int srcStride = params.i_width * 3;

    // convert to I420 for x264
    int h = sws_scale(sws, pic_raw.data, &srcStride, 0, height, pic_in.img.plane, pic_in.img.i_stride);
    if (h != height){
        ROS_ERROR("scale failed: %d", h);
        return false;
    }

    // and encode and store into pic_out
    pic_in.i_pts = pts;

    int frame_size = x264_encoder_encode(encoder, &nals, &num_nals, &pic_in, &pic_out);
    // ROS_INFO("size : %d / %d // Num nals : %d // Frame Size : %d ",sizeof(nals[0].p_payload),frame_size, num_nals, nals[0].i_payload);
    if (frame_size){
        
        ROS_INFO("Num nals : %d",num_nals);
        
        static bool alreadydone = false;
        if(!alreadydone){
            x264_encoder_headers(encoder, &nals, &num_nals);
            alreadydone = true;
        }

        for(int i = 0 ; i < num_nals ; i++){
            Out.push(nals[i]);
            // Out_.push(nals[i]);
        }
    }

    pts++;
    
    envir().taskScheduler().triggerEvent(eventTriggerId, this);

    return true;
}

void H264SourceRTP::deliverFrame0(void* clientData){
    // ROS_INFO("deliverFrame0");

    ((H264SourceRTP*)clientData)->deliverFrame();
}

void H264SourceRTP::doGetNextFrame(){
    // ROS_INFO("doGetNextFrame");

    deliverFrame();
}

void H264SourceRTP::deliverFrame(){
    if(!isCurrentlyAwaitingData()) return;

    // ROS_INFO("deliverFrame");

    x264_nal_t nalToDeliver;

    fDurationInMicroseconds = 33333;

    gettimeofday(&fPresentationTime, NULL);
    
    ROS_INFO("QUEUE size : %d", Out.size());
    // ROS_INFO("QUEUE size : %d", Out_.the_queue.size());
    
    if(!Out.empty()){   
        nalToDeliver = Out.front();
        Out.pop();
        // Out_.wait_and_pop(nalToDeliver);
        
        uint8_t* newFrameDataStart = (uint8_t*)0xD15EA5E;

        newFrameDataStart = (uint8_t*)(nalToDeliver.p_payload);

        if (nalToDeliver.i_payload > fMaxSize) {
            fFrameSize = fMaxSize;
            fNumTruncatedBytes = nalToDeliver.i_payload - fMaxSize;
        }
        else {
            fFrameSize = nalToDeliver.i_payload;
        }
         
        memcpy(fTo, nalToDeliver.p_payload, nalToDeliver.i_payload);
        FramedSource::afterGetting(this);
    }
}  

bool H264SourceRTP::openX264Encord(int width_, int height_, int fps_, AVPixelFormat in, AVPixelFormat out){
    width = width_;
    height = height_;
    fps = fps_;
    in_pixel_format = in;
    out_pixel_format = out;

#if !defined(DEBUG)
    params.i_log_level = X264_LOG_DEBUG;
#endif 

    x264_param_default_preset(&params, "ultrafast", "zerolatency");
    params.i_threads = 1;
    params.i_width = width;
    params.i_height = height;
    params.i_fps_num = fps;
    params.i_fps_den = 1;
    
    // Intra refres:
    params.i_keyint_max = fps;
    params.b_intra_refresh = 1;
    
    //Rate control:
    params.rc.i_rc_method = X264_RC_CRF;
    params.rc.f_rf_constant = 25;
    params.rc.f_rf_constant_max = 35;
    
    //For streaming:
    params.b_repeat_headers = 1;
    params.b_annexb = 1;
    x264_param_apply_profile(&params, "baseline");

    pic_in.i_type = X264_TYPE_AUTO;
    pic_in.img.i_csp = X264_CSP_I420;

    // @todo add validate which checks if all params are set (in/out width/height, fps,etc..);
    if (encoder){
        ROS_ERROR("Already opened. first call close()");
        return false;
    }

    // create the encoder using our params
    encoder = x264_encoder_open(&params);
    if (!encoder){
        ROS_ERROR("Cannot open the encoder");
        return false;
    }

    x264_picture_alloc(&pic_in, X264_CSP_I420, width, height);

    sws = sws_getContext(width, height, in_pixel_format,
                         width, height, out_pixel_format,
                         SWS_FAST_BILINEAR, NULL, NULL, NULL);

    if (!sws){
        ROS_ERROR("Cannot create SWS context");
        return false;
    }

    return true;   
}

#endif