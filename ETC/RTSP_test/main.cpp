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

int stop;

void sighandler(int){
       printf("SIGINT\n");
       stop = 1;
}

int main(){
	struct timeval tv;
	int verbose = 10;
	const char* in_devname = "/dev/video0";
	int ret;

	initLogger(verbose);
	V4L2DeviceParameters param(in_devname, 0, 0, 0, 0,verbose);
	V4l2Capture* videoCapture = V4l2Capture::create(param, V4l2Access::IOTYPE_MMAP);

	if(videoCapture == NULL)
		LOG(WARN) << "Cannot create V4L2 capture interface for device:" << in_devname;
	else{
		LOG(WARN) << "Create V4L2 capture" << in_devname;

		signal(SIGINT,sighandler);

		while(!stop){
			tv.tv_sec=1;
			tv.tv_usec=0;
			ret = videoCapture->isReadable(&tv);

			switch(ret){
			case 1:
			{
				u_int8_t buffer[videoCapture->getBufferSize()];
				char *buf = (char*)buffer;

				std::cout << &buf << "\n" << &buffer << "\n";

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
	}

	delete videoCapture;
}
