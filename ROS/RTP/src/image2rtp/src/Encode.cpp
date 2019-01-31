/*

  # X264Encoder

  Simple wrapper for x264 that you can use to encode into x264. Make
  sure to set all the params before calling `open()`. See below for the 
  members that the you need to set. 

 */
#ifndef X264_ENCODER
#define X264_ENCODER

#include <string>
#include <queue>

extern "C"{
#include <x264.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
}

#include <ros/console.h>

#include <liveMedia/liveMedia.hh>
#include <BasicUsageEnvironment/BasicUsageEnvironment.hh>
#include <groupsock/GroupsockHelper.hh>

class X264Encoder{
  public:
    X264Encoder();
    ~X264Encoder();
    bool open(int width_, int height_, int fps_, AVPixelFormat in, AVPixelFormat out); /* open for encoding */
    bool encode(const uint8_t *pixels);                                         /* encode the given data */
    bool isQueueEmpty();
    x264_nal_t getNalUnit();
    bool close();     

  private:
    bool validateSettings(); 
    void setParams();                                                           /* sets the x264 params */

    /* params the user should set */
    int width;
    int height;
    int fps;
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

    int pts;
    struct SwsContext *sws;

    /* Output Set */
    std::queue<x264_nal_t> Out;
    FILE* fp;
    
};

X264Encoder::X264Encoder()
    : width(0), height(0), fps(0), in_pixel_format(AV_PIX_FMT_NONE), out_pixel_format(AV_PIX_FMT_NONE), encoder(NULL), num_nals(0), pts(0){
    
    memset((char *)&pic_raw, 0, sizeof(pic_raw));
}

X264Encoder::~X264Encoder(){
    if (sws)
        close();
}

void X264Encoder::setParams(){

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

}


bool X264Encoder::open(int width_, int height_, int fps_, AVPixelFormat in, AVPixelFormat out){
    width = width_;
    height = height_;
    fps = fps_;
    in_pixel_format = in;
    out_pixel_format = out;

    if (!validateSettings()){
        return false;
    }

    // @todo add validate which checks if all params are set (in/out width/height, fps,etc..);
    if (encoder){
        ROS_ERROR("Already opened. first call close()");
        return false;
    }

    setParams();

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

    // // ROS image to H.264 Video file 
    // int r = 0;
    // int nheader = 0;
    // int header_size = 0;

    // std::string filename = "./test.h264";
    
    // fp = fopen(filename.c_str(), "w+b");
    // if (!fp){
    //     ROS_ERROR("Cannot open the h264 destination file");
    //     return  false;
    // }

    //   // write headers
    // r = x264_encoder_headers(encoder, &nals, &nheader);
    // if (r < 0){
    //     ROS_ERROR("x264_encoder_headers() failed");
    //     return false;
    // }

    // header_size = nals[0].i_payload + nals[1].i_payload + nals[2].i_payload;
    // if (!fwrite(nals[0].p_payload, header_size, 1, fp)){
    //     ROS_ERROR("Cannot write headers");
    //     return false;
    // }

    return true;   
}

bool X264Encoder::encode(const uint8_t *pixels){
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
    ROS_INFO("size : %d / %d",sizeof(nals[0].p_payload),frame_size);
    if (frame_size){
        // // Write File
        // if(!fwrite(nals[0].p_payload, frame_size, 1, fp)) {
        //     ROS_ERROR("Encode failed: %d", h);
        //     return false;
        // }

        for(int i = 0 ; i < num_nals ; i++){
            Out.push(nals[i]);
        }
    }
    
    pts++;

    return true;
}

bool X264Encoder::close(){
    if (encoder){
        x264_picture_clean(&pic_in);
        memset((char *)&pic_in, 0, sizeof(pic_in));
        memset((char *)&pic_out, 0, sizeof(pic_out));

        x264_encoder_close(encoder);
        encoder = NULL;
    }

    if (sws){
        sws_freeContext(sws);
        sws = NULL;
    }

    memset((char *)&pic_raw, 0, sizeof(pic_raw));

    if (fp){
        fclose(fp);
        fp = NULL;
    }

    return true;
}

bool X264Encoder::validateSettings(){
    if (!width){
        ROS_ERROR("No width set");
        return false;
    }
    
    if (!height){
        ROS_ERROR("No height set");
        return false;
    }

    if (!fps){
        ROS_ERROR("No fps set");
        return false;
    }

    if (in_pixel_format == AV_PIX_FMT_NONE){
        ROS_ERROR("No in_pixel_format set");
        return false;
    }

    if (out_pixel_format == AV_PIX_FMT_NONE){
        ROS_ERROR("No out_pixel_format set");
        return false;
    }
    return true;
}

bool X264Encoder::isQueueEmpty(){
    if(Out.empty())
        return true;
    else   
        return false;
}

x264_nal_t X264Encoder::getNalUnit(){
    x264_nal_t nal;
    nal = Out.front();
    Out.pop();
    return nal;
}

#endif
