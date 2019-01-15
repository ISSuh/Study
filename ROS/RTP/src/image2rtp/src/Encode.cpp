/*

  # X264Encoder

  Simple wrapper for x264 that you can use to encode into x264. Make
  sure to set all the params before calling `open()`. See below for the 
  members that the you need to set. 

 */
#ifndef X264_ENCODER
#define X264_ENCODER

#include <string>
extern "C"{
#include <x264.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
}
#include <ros/console.h>

class X264Encoder{
  public:
    X264Encoder(int _width, int _height, int _fps);
    ~X264Encoder();
    bool open();                                    /* open for encoding */
    bool encode(char *pixels);                      /* encode the given data */
    bool close();                                   /* close the encoder and file, frees all memory */
  private:
    bool validateSettings(); /* validates if all params are set correctly, like width,height, etc.. */
    void setParams();        /* sets the x264 params */

    /* params the user should set */
    int width;
    int height;
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
};

X264Encoder::X264Encoder(int _width, int _height, int _fps)
    : width(_width), height(_height), in_pixel_format(AV_PIX_FMT_NONE), out_pixel_format(AV_PIX_FMT_NONE), fps(_fps), encoder(NULL), num_nals(0), pts(0){
    
    memset((char *)&pic_raw, 0, sizeof(pic_raw));
}

X264Encoder::~X264Encoder(){
    if (sws)
        close();
    
}

bool X264Encoder::open(){

    if (!validateSettings()){
        return false;
    }

    // @todo add validate which checks if all params are set (in/out width/height, fps,etc..);
    if (encoder){
        ROS_ERROR("Already opened. first call close()");
        return false;
    }

    if (out_pixel_format != AV_PIX_FMT_YUV420P){
        ROS_ERROR("At this moment the output format must be AV_PIX_FMT_YUV420P");
        return false;
    }

    x264_picture_alloc(&pic_in, X264_CSP_I420, width, height);

    setParams();

    // create the encoder using our params
    encoder = x264_encoder_open(&params);
    if (!encoder){
        ROS_ERROR("Cannot open the encoder");
        return false;
    }

   sws = sws_getContext(width, height, in_pixel_format,
                         width, height, out_pixel_format,
                         SWS_FAST_BILINEAR, NULL, NULL, NULL);

    if (!sws){
        ROS_ERROR("Cannot create SWS context");
        return false;
    }


    pts = 0;

    return true;   
}

bool X264Encoder::encode(char *pixels){
    if (!sws){
        ROS_ERROR("Not initialized, so cannot encode");
        return false;
    }

    // copy the pixels into our "raw input" container.
    int bytes_filled = avpicture_fill(&pic_raw, (uint8_t *)pixels, in_pixel_format, width, height);
    if (!bytes_filled){
        ROS_ERROR("Cannot fill the raw input buffer");
        return false;
    }

    // convert to I420 for x264
    int h = sws_scale(sws, pic_raw.data, pic_raw.linesize, 0,
                      height, pic_in.img.plane, pic_in.img.i_stride);

    if (h != height){
        ROS_ERROR("scale failed: %d", h);
        return false;
    }

    // and encode and store into pic_out
    pic_in.i_pts = pts;

    int frame_size = x264_encoder_encode(encoder, &nals, &num_nals, &pic_in, &pic_out);
    if (!frame_size){
        ROS_ERROR("Encode failed: %d", h);
        return false;
    }

    pts++;

    return true;
}

bool X264Encoder::close()
{
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
    
    return true;
}

void X264Encoder::setParams(){

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
    pic_in.img.i_csp = X264_CSP_I420
}

bool X264Encoder::validateSettings(){
    if (!width){
        ROS_ERROR("No in_width set");
        return false;
    }
    
    if (!height){
        ROS_ERROR("No in_height set");
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

#endif
