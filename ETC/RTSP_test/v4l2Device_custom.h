#ifndef V4L2DEVICE_CUSTOM
#define V4L2DEVICE_CUSTOM

#include <list>
#include <iostream>
#include <sys/time.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#include "V4l2Output.h"
#include "V4l2Capture.h"
#include "logger.h"

#include <liveMedia/liveMedia.hh>
#include <UsageEnvironment/UsageEnvironment.hh>
#include <BasicUsageEnvironment/BasicUsageEnvironment.hh>
#include <liveMedia/ByteStreamFileSource.hh>
#include <groupsock/GroupsockHelper.hh>

/*class DeviceInterface
 {
 public:
 virtual size_t read(char* buffer, size_t bufferSize) = 0;
 virtual int getFd() = 0;
 virtual unsigned long getBufferSize() = 0;
 virtual int getWidth() = 0;
 virtual int getHeight() = 0;
 virtual ~DeviceInterface() {};
 };

 class V4L2Device_Custom : public FramedSource{
 public:

 struct Frame{
 Frame(char* buffer, int size, timeval timestamp) : m_buffer(buffer), m_size(size), m_timestamp(timestamp) {};
 Frame(const Frame&);
 Frame& operator=(const Frame&);
 ~Frame()  { delete [] m_buffer; };

 char* m_buffer;
 unsigned int m_size;
 timeval m_timestamp;
 };

 class Stats{
 public:
 Stats(const std::string & msg) : m_fps(0), m_fps_sec(0), m_size(0), m_msg(msg) {};

 public:
 int notify(int tv_sec, int framesize);

 protected:
 int m_fps;
 int m_fps_sec;
 int m_size;
 const std::string m_msg;
 };

 static V4L2Device_Custom* Create(UsageEnvironment& env, DeviceInterface * device,
 int outputFd, unsigned int queueSize);
 int getWidth() { return m_device->getWidth(); };
 int getHeight() { return m_device->getHeight(); };

 protected:
 V4L2Device_Custom(UsageEnvironment& env, DeviceInterface * device,
 int outputFd, unsigned int queueSize);
 ~V4L2Device_Custom();
 virtual void doGetNextFrame();
 virtual void doStopGettingFrames();
 int getNextFrame();

 static void deliverFrameStub(void* clientData) {((V4L2Device_Custom*) clientData)->deliverFrame();};
 void deliverFrame();
 static void incomingPacketHandlerStub(void* clientData, int mask) { ((V4L2Device_Custom*) clientData)->incomingPacketHandler(); };
 void incomingPacketHandler();
 private:
 std::list<Frame*> m_captureQueue;
 Stats m_in;
 Stats m_out;
 EventTriggerId m_eventTriggerId;
 int m_outfd;
 DeviceInterface * m_device;
 unsigned int m_queueSize;

 struct timeval tv;
 };*/

class DeviceInterface_Custom {
public:
	static DeviceInterface_Custom* Create(u_int8_t *buffer,
			u_int64_t *bufferSize, unsigned int width, unsigned int height,
			const char *deviceName, unsigned int formet, unsigned int fps,
			int verbose);

	int getBufSize() {
		return this->bufSize;
	}
	int getWidth() {
		return this->width;
	}
	int getHeight() {
		return this->height;
	}

protected:
	DeviceInterface_Custom(u_int8_t *buffer, u_int64_t *buffersize,
			unsigned int width, unsigned int height, const char *deviceName,
			unsigned int formet, unsigned int fps, int verbose);
	~DeviceInterface_Custom();

	static void* threadStub(void* clientData) {
		return ((DeviceInterface_Custom*) clientData)->thread();
	}
	void* thread(void);
	static void sighandler(int) {
		printf("SIGINT\n");
		stop = 1;
	}

private:
	unsigned int verbose;
	unsigned int formet;
	unsigned int width;
	unsigned int height;
	unsigned int fps;
	const char *deviceName;
	u_int8_t *buf;
	u_int64_t bufSize;
	struct timeval tv;

	static int stop;

	V4L2DeviceParameters *param;
	V4l2Capture* videoCapture;

	pthread_t thid;
//	pthread_mutex_t mutex;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DeviceParameters_Custom {
public:
	DeviceParameters_Custom(const char *deviceName, unsigned int formet,
								unsigned int width,unsigned int height,
								unsigned int fps,unsigned int verbose);
	const char *deviceName;
	unsigned int formet;
	unsigned int width;
	unsigned int height;
	unsigned int fps;
	unsigned int verbose;

	V4L2DeviceParameters *param;
};

class DeviceSource_Custom: public FramedSource {
public:
	static DeviceSource_Custom* createNew(UsageEnvironment& env, DeviceParameters_Custom params);

public:
	static EventTriggerId eventTriggerId;
	// Note that this is defined here to be a static class variable, because this code is intended to illustrate how to
	// encapsulate a *single* device - not a set of devices.
	// You can, however, redefine this to be a non-static member variable.

protected:
	DeviceSource_Custom(UsageEnvironment& env, DeviceParameters_Custom params);
	// called only by createNew(), or by subclass constructors
	virtual ~DeviceSource_Custom();

private:
	// redefined virtual functions:
	virtual void doGetNextFrame();
	//virtual void doStopGettingFrames(); // optional

private:
	static void deliverFrame0(void* clientData);
	void deliverFrame();

	static void sighandler(int) {
		printf("SIGINT\n");
		stop = 1;
	}

private:
	static unsigned referenceCount; // used to count how many instances of this class currently exist
	DeviceParameters_Custom fParams;

	V4l2Capture* videoCapture;

	struct timeval tv;
	static u_int8_t *buf;
	u_int64_t bufSize;

	static int stop;
};
#endif //V4L2DEVICE
