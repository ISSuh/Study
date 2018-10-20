#include "v4l2Device_custom.h"

#include <fcntl.h>
#include <iomanip>
#include <sstream>
#include <pthread.h>

// project
#include "logger.h"

/*V4L2Device_Custom::V4L2Device_Custom(UsageEnvironment& env, DeviceInterface * device,
												int outputFd, unsigned int queueSize)
: FramedSource(env),
m_in("in"),
m_out("out") ,
m_outfd(outputFd),
m_device(device),
m_queueSize(queueSize){
	m_eventTriggerId = envir().taskScheduler().createEventTrigger(V4L2Device_Custom::deliverFrameStub);
	if (m_device)
		envir().taskScheduler().turnOnBackgroundReadHandling( m_device->getFd(),
															V4L2Device_Custom::incomingPacketHandlerStub, this);
}

V4L2Device_Custom::~V4L2Device_Custom(){
	envir().taskScheduler().deleteEventTrigger(m_eventTriggerId);
	delete m_device;
}

V4L2Device_Custom *V4L2Device_Custom::V4L2Device_Custom(UsageEnvironment& env, DeviceInterface * device,
																	int outputFd, unsigned int queueSize){
	V4L2Device_Custom *sourse;
	if (device)
		source = new V4L2DeviceSource(env, device, outputFd, queueSize, useThread);

	return sourse;
}
void V4L2Device_Custom::doGetNextFrame(){
	deliverFrame();
}

void V4L2Device_Custom::doStopGettingFrames(){
	LOG(NOTICE) << "V4L2DeviceSource::doStopGettingFrames";
	FramedSource::doStopGettingFrames();
}

void V4L2Device_Custom::getNextFrame(){

}

void V4L2DeviceSource::deliverFrame(){

}

void V4L2DeviceSource::incomingPacketHandler()
{
	if (this->getNextFrame() <= 0)
		handleClosure(this);

}*/


int DeviceInterface_Custom::stop = 0;

DeviceInterface_Custom *DeviceInterface_Custom::Create(u_int8_t *buffer, u_int64_t *bufferSize,
							unsigned int width, unsigned int height, const char *deviceName,
							unsigned int formet, unsigned int fps, int verbose){
	DeviceInterface_Custom* source ;
	source = new DeviceInterface_Custom(buffer,bufferSize,width,height,deviceName,formet,fps,verbose);
	return source;
}

DeviceInterface_Custom::DeviceInterface_Custom(u_int8_t *buffer, u_int64_t *bufferSize,
														unsigned int width, unsigned int height,
														const char *deviceName, unsigned int formet,
														unsigned int fps, int verbose)
		:verbose(verbose),
		 formet(formet),
		 width(width),
		 height(height),
		 fps(fps),
		 deviceName(deviceName),
		 buf(buffer){
	memset(&thid, 0, sizeof(thid));
//	memset(&mutex, 0, sizeof(mutex));

	initLogger(verbose);

	this->param = new V4L2DeviceParameters(deviceName,formet,width,height,fps,verbose);
	this->videoCapture = V4l2Capture::create(*param,V4l2Access::IOTYPE_MMAP);

	if(videoCapture == NULL)
		LOG(WARN) << "Cannot create V4L2 capture interface for device:" << deviceName;
	else{
		LOG(WARN) << "Create V4L2 capture" << deviceName;
		bufSize = videoCapture->getBufferSize();
		bufferSize = &bufSize;

		signal(SIGINT,sighandler);

		int err = pthread_create(&thid, NULL, threadStub, this);
		if(err)
			std::cout << "thread create Error : " << err;
	}
}

DeviceInterface_Custom::~DeviceInterface_Custom(){
	pthread_join(thid, NULL);
	delete videoCapture;
}

void *DeviceInterface_Custom::thread(void){
	int ret;

	while(!stop){
		tv.tv_sec=1;
		tv.tv_usec=0;
		ret = videoCapture->isReadable(&tv);

		switch(ret){
		case 1:
		{
			char buf[this->bufSize];
			int rsize = videoCapture->read(buf,sizeof(buf));

			if (rsize == -1){
				LOG(NOTICE) << "stop " << strerror(errno);
				stop = 1;
			}
			else
				LOG(NOTICE) << "play " << strerror(errno);
			break;
		}
		case -1:
		{
			LOG(NOTICE) << "stop " << strerror(errno);
			stop = 1;
			break;
		}
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DeviceParameters_Custom::DeviceParameters_Custom(const char *deviceName, unsigned int formet,
														unsigned int width,unsigned int height,
														unsigned int fps,unsigned int verbose)
: deviceName(deviceName),
  formet(formet),
  width(width),
  height(height),
  fps(fps),
  verbose(verbose){
	initLogger(verbose);

	param = new V4L2DeviceParameters(deviceName,formet,
												width,height,
												fps,verbose);
}


EventTriggerId DeviceSource_Custom::eventTriggerId = 0;
unsigned 		 DeviceSource_Custom::referenceCount = 0;
u_int8_t 		*DeviceSource_Custom::buf			  = NULL;
int				 DeviceSource_Custom::stop			  = 0;

DeviceSource_Custom* DeviceSource_Custom::createNew(UsageEnvironment& env, DeviceParameters_Custom params) {
  return new DeviceSource_Custom(env, params);
}

DeviceSource_Custom::DeviceSource_Custom(UsageEnvironment& env, DeviceParameters_Custom params)
  : FramedSource(env), fParams(params) {
  if (referenceCount == 0) {
    // Any global initialization of the device would be done here:
    //%%% TO BE WRITTEN %%%

		videoCapture = V4l2Capture::create(*fParams.param,V4l2Access::IOTYPE_MMAP);

		bufSize = videoCapture->getBufferSize();
		buf = new u_int8_t[bufSize];

		signal(SIGINT,sighandler);
  }
  ++referenceCount;

  // Any instance-specific initialization of the device would be done here:
  //%%% TO BE WRITTEN %%%

  // We arrange here for our "deliverFrame" member function to be called
  // whenever the next frame of data becomes available from the device.
  //
  // If the device can be accessed as a readable socket, then one easy way to do this is using a call to
  //     envir().taskScheduler().turnOnBackgroundReadHandling( ... )
  // (See examples of this call in the "liveMedia" directory.)
  //
  // If, however, the device *cannot* be accessed as a readable socket, then instead we can implement it using 'event triggers':
  // Create an 'event trigger' for this device (if it hasn't already been done):
  if (eventTriggerId == 0) {
    eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
  }
}

DeviceSource_Custom::~DeviceSource_Custom() {
  // Any instance-specific 'destruction' (i.e., resetting) of the device would be done here:
  //%%% TO BE WRITTEN %%%

	delete buf;

  --referenceCount;
  if (referenceCount == 0) {
    // Any global 'destruction' (i.e., resetting) of the device would be done here:
    //%%% TO BE WRITTEN %%%

    // Reclaim our 'event trigger'
    envir().taskScheduler().deleteEventTrigger(eventTriggerId);
    eventTriggerId = 0;
  }
}

void DeviceSource_Custom::doGetNextFrame() {
  // This function is called (by our 'downstream' object) when it asks for new data.

  // Note: If, for some reason, the source device stops being readable (e.g., it gets closed), then you do the following:


	if (stop /* the source stops being readable */ /*%%% TO BE WRITTEN %%%*/) {
		handleClosure();
		return;
	}
	else {
		while(!stop){
			tv.tv_sec=1;
			tv.tv_usec=0;

			int ret = videoCapture->isReadable(&tv);

			switch(ret){
			case 1:{
				int rsize = videoCapture->read((char*)buf,bufSize);
				LOG(NOTICE) << buf << strerror(errno);
				if (rsize == -1){
					LOG(NOTICE) << "stop " << strerror(errno);
					stop = 1;
				}
				else
					LOG(NOTICE) << "play " << strerror(errno);
				break;
			}
			case -1:{
				LOG(NOTICE) << "stop " << strerror(errno);
				stop = 1;
				break;
			}
			}

			deliverFrame();
		}
	}

  // If a new frame of data is immediately available to be delivered, then do this now:
//  if (0 /* a new frame of data is immediately available to be delivered*/ /*%%% TO BE WRITTEN %%%*/) {

//  }

  // No new data is immediately available to be delivered.  We don't do anything more here.
  // Instead, our event trigger must be called (e.g., from a separate sthread) when new data becomes available.
}

void DeviceSource_Custom::deliverFrame0(void* clientData) {
  ((DeviceSource_Custom*)clientData)->deliverFrame();
}

void DeviceSource_Custom::deliverFrame() {
  // This function is called when new frame data is available from the device.
  // We deliver this data by copying it to the 'downstream' object, using the following parameters (class members):
  // 'in' parameters (these should *not* be modified by this function):
  //     fTo: The frame data is copied to this address.
  //         (Note that the variable "fTo" is *not* modified.  Instead,
  //          the frame data is copied to the address pointed to by "fTo".)
  //     fMaxSize: This is the maximum number of bytes that can be copied
  //         (If the actual frame is larger than this, then it should
  //          be truncated, and "fNumTruncatedBytes" set accordingly.)
  // 'out' parameters (these are modified by this function):
  //     fFrameSize: Should be set to the delivered frame size (<= fMaxSize).
  //     fNumTruncatedBytes: Should be set iff the delivered frame would have been
  //         bigger than "fMaxSize", in which case it's set to the number of bytes
  //         that have been omitted.
  //     fPresentationTime: Should be set to the frame's presentation time
  //         (seconds, microseconds).  This time must be aligned with 'wall-clock time' - i.e., the time that you would get
  //         by calling "gettimeofday()".
  //     fDurationInMicroseconds: Should be set to the frame's duration, if known.
  //         If, however, the device is a 'live source' (e.g., encoded from a camera or microphone), then we probably don't need
  //         to set this variable, because - in this case - data will never arrive 'early'.
  // Note the code below.

  if (!isCurrentlyAwaitingData()) return; // we're not ready for the data yet

  u_int8_t* newFrameDataStart = (u_int8_t*)buf; //%%% TO BE WRITTEN %%%
  unsigned newFrameSize = bufSize; //%%% TO BE WRITTEN %%%

  // Deliver the data here:
  if (newFrameSize > fMaxSize) {
    fFrameSize = fMaxSize;
    fNumTruncatedBytes = newFrameSize - fMaxSize;
  } else {
    fFrameSize = newFrameSize;
  }
  gettimeofday(&fPresentationTime, NULL); // If you have a more accurate time - e.g., from an encoder - then use that instead.
  // If the device is *not* a 'live source' (e.g., it comes instead from a file or buffer), then set "fDurationInMicroseconds" here.
  memmove(fTo, newFrameDataStart, fFrameSize);

  // After delivering the data, inform the reader that it is now available:
  FramedSource::afterGetting(this);
}


// The following code would be called to signal that a new frame of data has become available.
// This (unlike other "LIVE555 Streaming Media" library code) may be called from a separate thread.
// (Note, however, that "triggerEvent()" cannot be called with the same 'event trigger id' from different threads.
// Also, if you want to have multiple device threads, each one using a different 'event trigger id', then you will need
// to make "eventTriggerId" a non-static member variable of "DeviceSource".)
/*void signalNewFrameData() {
  TaskScheduler* ourScheduler = NULL; //%%% TO BE WRITTEN %%%
  DeviceSource* ourDevice  = NULL; //%%% TO BE WRITTEN %%%

  if (ourScheduler != NULL) { // sanity check
    ourScheduler->triggerEvent(DeviceSource::eventTriggerId, ourDevice);
  }
}*/
