#ifndef MY_TASK_SCHEDULER
#define MY_TASK_SCHEDULER

#include "ros/ros.h"

#include <BasicUsageEnvironment/BasicUsageEnvironment0.hh>
#include <BasicUsageEnvironment/BasicUsageEnvironment.hh>
#include <BasicUsageEnvironment/HandlerSet.hh>
#include <stdio.h>

class MyTaskScheduler : public BasicTaskScheduler0{
  public:
    static MyTaskScheduler *createNew(unsigned maxSchedulerGranularity = 10000 /*microseconds*/);
    // "maxSchedulerGranularity" (default value: 10 ms) specifies the maximum time that we wait (in "select()") before
    // returning to the event loop to handle non-socket or non-timer-based events, such as 'triggered events'.
    // You can change this is you wish (but only if you know what you're doing!), or set it to 0, to specify no such maximum time.
    // (You should set it to 0 only if you know that you will not be using 'event triggers'.)
    virtual ~MyTaskScheduler();

    virtual void doEventLoop(char volatile* watchVariable);

  protected:
    MyTaskScheduler(unsigned maxSchedulerGranularity);
    // called only by "createNew()"

    static void schedulerTickTask(void *clientData);
    void schedulerTickTask();

  protected:
    // Redefined virtual functions:
    virtual void SingleStep(unsigned maxDelayTime = 0);

    virtual void setBackgroundHandling(int socketNum, int conditionSet, BackgroundHandlerProc *handlerProc, void *clientData);
    virtual void moveSocketHandling(int oldSocketNum, int newSocketNum);

  protected:
    unsigned fMaxSchedulerGranularity;

    // To implement background operations:
    int fMaxNumSockets;
    fd_set fReadSet;
    fd_set fWriteSet;
    fd_set fExceptionSet;

  private:
#if defined(__WIN32__) || defined(_WIN32)
    // Hack to work around a bug in Windows' "select()" implementation:
    int fDummySocketNum;
#endif
};

MyTaskScheduler* MyTaskScheduler::createNew(unsigned maxSchedulerGranularity) {
	return new MyTaskScheduler(maxSchedulerGranularity);
}

MyTaskScheduler::MyTaskScheduler(unsigned maxSchedulerGranularity)
  : fMaxSchedulerGranularity(maxSchedulerGranularity), fMaxNumSockets(0)
#if defined(__WIN32__) || defined(_WIN32)
  , fDummySocketNum(-1)
#endif
{
  FD_ZERO(&fReadSet);
  FD_ZERO(&fWriteSet);
  FD_ZERO(&fExceptionSet);

  if (maxSchedulerGranularity > 0) schedulerTickTask(); // ensures that we handle events frequently
}

MyTaskScheduler::~MyTaskScheduler() {
#if defined(__WIN32__) || defined(_WIN32)
  if (fDummySocketNum >= 0) closeSocket(fDummySocketNum);
#endif
}

void MyTaskScheduler::schedulerTickTask(void* clientData) {
  ((MyTaskScheduler*)clientData)->schedulerTickTask();
}

void MyTaskScheduler::schedulerTickTask() {
  scheduleDelayedTask(fMaxSchedulerGranularity, schedulerTickTask, this);
}

#ifndef MILLION
#define MILLION 1000000
#endif

void MyTaskScheduler::SingleStep(unsigned maxDelayTime) {
  fd_set readSet = fReadSet; // make a copy for this select() call
  fd_set writeSet = fWriteSet; // ditto
  fd_set exceptionSet = fExceptionSet; // ditto

  DelayInterval const& timeToDelay = fDelayQueue.timeToNextAlarm();
  struct timeval tv_timeToDelay;
  tv_timeToDelay.tv_sec = timeToDelay.seconds();
  tv_timeToDelay.tv_usec = timeToDelay.useconds();
  // Very large "tv_sec" values cause select() to fail.
  // Don't make it any larger than 1 million seconds (11.5 days)
  const long MAX_TV_SEC = MILLION;
  if (tv_timeToDelay.tv_sec > MAX_TV_SEC) {
    tv_timeToDelay.tv_sec = MAX_TV_SEC;
  }
  // Also check our "maxDelayTime" parameter (if it's > 0):
  if (maxDelayTime > 0 &&
      (tv_timeToDelay.tv_sec > (long)maxDelayTime/MILLION ||
       (tv_timeToDelay.tv_sec == (long)maxDelayTime/MILLION &&
	tv_timeToDelay.tv_usec > (long)maxDelayTime%MILLION))) {
    tv_timeToDelay.tv_sec = maxDelayTime/MILLION;
    tv_timeToDelay.tv_usec = maxDelayTime%MILLION;
  }

  int selectResult = select(fMaxNumSockets, &readSet, &writeSet, &exceptionSet, &tv_timeToDelay);
  if (selectResult < 0) {
#if defined(__WIN32__) || defined(_WIN32)
    int err = WSAGetLastError();
    // For some unknown reason, select() in Windoze sometimes fails with WSAEINVAL if
    // it was called with no entries set in "readSet".  If this happens, ignore it:
    if (err == WSAEINVAL && readSet.fd_count == 0) {
      err = EINTR;
      // To stop this from happening again, create a dummy socket:
      if (fDummySocketNum >= 0) closeSocket(fDummySocketNum);
      fDummySocketNum = socket(AF_INET, SOCK_DGRAM, 0);
      FD_SET((unsigned)fDummySocketNum, &fReadSet);
    }
    if (err != EINTR) {
#else
    if (errno != EINTR && errno != EAGAIN) {
#endif
	// Unexpected error - treat this as fatal:
#if !defined(_WIN32_WCE)
	perror("MyTaskScheduler::SingleStep(): select() fails");
	// Because this failure is often "Bad file descriptor" - which is caused by an invalid socket number (i.e., a socket number
	// that had already been closed) being used in "select()" - we print out the sockets that were being used in "select()",
	// to assist in debugging:
	fprintf(stderr, "socket numbers used in the select() call:");
	for (int i = 0; i < 10000; ++i) {
	  if (FD_ISSET(i, &fReadSet) || FD_ISSET(i, &fWriteSet) || FD_ISSET(i, &fExceptionSet)) {
	    fprintf(stderr, " %d(", i);
	    if (FD_ISSET(i, &fReadSet)) fprintf(stderr, "r");
	    if (FD_ISSET(i, &fWriteSet)) fprintf(stderr, "w");
	    if (FD_ISSET(i, &fExceptionSet)) fprintf(stderr, "e");
	    fprintf(stderr, ")");
	  }
	}
	fprintf(stderr, "\n");
#endif
	internalError();
      }
  }

  // Call the handler function for one readable socket:
  HandlerIterator iter(*fHandlers);
  HandlerDescriptor* handler;
  // To ensure forward progress through the handlers, begin past the last
  // socket number that we handled:
  if (fLastHandledSocketNum >= 0) {
    while ((handler = iter.next()) != NULL) {
      if (handler->socketNum == fLastHandledSocketNum) break;
    }
    if (handler == NULL) {
      fLastHandledSocketNum = -1;
      iter.reset(); // start from the beginning instead
    }
  }
  while ((handler = iter.next()) != NULL) {
    int sock = handler->socketNum; // alias
    int resultConditionSet = 0;
    if (FD_ISSET(sock, &readSet) && FD_ISSET(sock, &fReadSet)/*sanity check*/) resultConditionSet |= SOCKET_READABLE;
    if (FD_ISSET(sock, &writeSet) && FD_ISSET(sock, &fWriteSet)/*sanity check*/) resultConditionSet |= SOCKET_WRITABLE;
    if (FD_ISSET(sock, &exceptionSet) && FD_ISSET(sock, &fExceptionSet)/*sanity check*/) resultConditionSet |= SOCKET_EXCEPTION;
    if ((resultConditionSet&handler->conditionSet) != 0 && handler->handlerProc != NULL) {
      fLastHandledSocketNum = sock;
          // Note: we set "fLastHandledSocketNum" before calling the handler,
          // in case the handler calls "doEventLoop()" reentrantly.
      (*handler->handlerProc)(handler->clientData, resultConditionSet);
      break;
    }
  }
  if (handler == NULL && fLastHandledSocketNum >= 0) {
    // We didn't call a handler, but we didn't get to check all of them,
    // so try again from the beginning:
    iter.reset();
    while ((handler = iter.next()) != NULL) {
      int sock = handler->socketNum; // alias
      int resultConditionSet = 0;
      if (FD_ISSET(sock, &readSet) && FD_ISSET(sock, &fReadSet)/*sanity check*/) resultConditionSet |= SOCKET_READABLE;
      if (FD_ISSET(sock, &writeSet) && FD_ISSET(sock, &fWriteSet)/*sanity check*/) resultConditionSet |= SOCKET_WRITABLE;
      if (FD_ISSET(sock, &exceptionSet) && FD_ISSET(sock, &fExceptionSet)/*sanity check*/) resultConditionSet |= SOCKET_EXCEPTION;
      if ((resultConditionSet&handler->conditionSet) != 0 && handler->handlerProc != NULL) {
	fLastHandledSocketNum = sock;
	    // Note: we set "fLastHandledSocketNum" before calling the handler,
            // in case the handler calls "doEventLoop()" reentrantly.
	(*handler->handlerProc)(handler->clientData, resultConditionSet);
	break;
      }
    }
    if (handler == NULL) fLastHandledSocketNum = -1;//because we didn't call a handler
  }

  // Also handle any newly-triggered event (Note that we do this *after* calling a socket handler,
  // in case the triggered event handler modifies The set of readable sockets.)
  if (fTriggersAwaitingHandling != 0) {
    if (fTriggersAwaitingHandling == fLastUsedTriggerMask) {
      // Common-case optimization for a single event trigger:
      fTriggersAwaitingHandling &=~ fLastUsedTriggerMask;
      if (fTriggeredEventHandlers[fLastUsedTriggerNum] != NULL) {
	(*fTriggeredEventHandlers[fLastUsedTriggerNum])(fTriggeredEventClientDatas[fLastUsedTriggerNum]);
      }
    } else {
      // Look for an event trigger that needs handling (making sure that we make forward progress through all possible triggers):
      unsigned i = fLastUsedTriggerNum;
      EventTriggerId mask = fLastUsedTriggerMask;

      do {
	i = (i+1)%MAX_NUM_EVENT_TRIGGERS;
	mask >>= 1;
	if (mask == 0) mask = 0x80000000;

	if ((fTriggersAwaitingHandling&mask) != 0) {
	  fTriggersAwaitingHandling &=~ mask;
	  if (fTriggeredEventHandlers[i] != NULL) {
	    (*fTriggeredEventHandlers[i])(fTriggeredEventClientDatas[i]);
	  }

	  fLastUsedTriggerMask = mask;
	  fLastUsedTriggerNum = i;
	  break;
	}
      } while (i != fLastUsedTriggerNum);
    }
  }

  // Also handle any delayed event that may have come due.
  fDelayQueue.handleAlarm();
}

void MyTaskScheduler
  ::setBackgroundHandling(int socketNum, int conditionSet, BackgroundHandlerProc* handlerProc, void* clientData) {
  if (socketNum < 0) return;
#if !defined(__WIN32__) && !defined(_WIN32) && defined(FD_SETSIZE)
  if (socketNum >= (int)(FD_SETSIZE)) return;
#endif
  FD_CLR((unsigned)socketNum, &fReadSet);
  FD_CLR((unsigned)socketNum, &fWriteSet);
  FD_CLR((unsigned)socketNum, &fExceptionSet);
  if (conditionSet == 0) {
    fHandlers->clearHandler(socketNum);
    if (socketNum+1 == fMaxNumSockets) {
      --fMaxNumSockets;
    }
  } else {
    fHandlers->assignHandler(socketNum, conditionSet, handlerProc, clientData);
    if (socketNum+1 > fMaxNumSockets) {
      fMaxNumSockets = socketNum+1;
    }
    if (conditionSet&SOCKET_READABLE) FD_SET((unsigned)socketNum, &fReadSet);
    if (conditionSet&SOCKET_WRITABLE) FD_SET((unsigned)socketNum, &fWriteSet);
    if (conditionSet&SOCKET_EXCEPTION) FD_SET((unsigned)socketNum, &fExceptionSet);
  }
}

void MyTaskScheduler::moveSocketHandling(int oldSocketNum, int newSocketNum) {
  if (oldSocketNum < 0 || newSocketNum < 0) return; // sanity check
#if !defined(__WIN32__) && !defined(_WIN32) && defined(FD_SETSIZE)
  if (oldSocketNum >= (int)(FD_SETSIZE) || newSocketNum >= (int)(FD_SETSIZE)) return; // sanity check
#endif
  if (FD_ISSET(oldSocketNum, &fReadSet)) {FD_CLR((unsigned)oldSocketNum, &fReadSet); FD_SET((unsigned)newSocketNum, &fReadSet);}
  if (FD_ISSET(oldSocketNum, &fWriteSet)) {FD_CLR((unsigned)oldSocketNum, &fWriteSet); FD_SET((unsigned)newSocketNum, &fWriteSet);}
  if (FD_ISSET(oldSocketNum, &fExceptionSet)) {FD_CLR((unsigned)oldSocketNum, &fExceptionSet); FD_SET((unsigned)newSocketNum, &fExceptionSet);}
  fHandlers->moveHandler(oldSocketNum, newSocketNum);

  if (oldSocketNum+1 == fMaxNumSockets) {
    --fMaxNumSockets;
  }
  if (newSocketNum+1 > fMaxNumSockets) {
    fMaxNumSockets = newSocketNum+1;
  }
}

void MyTaskScheduler::doEventLoop(char volatile* watchVariable) {
  // Repeatedly loop, handling readble sockets and timed events:

  while (1) {
    if (watchVariable != NULL && *watchVariable != 0) break;
    ros::spinOnce();
    SingleStep();    
  }
}

#endif