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
