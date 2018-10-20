cmake_minimum_required(VERSION 2.6)


# set project name from current directory
project(RTSP_TEST)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "-Wall")

set(SRC_FILES
	RTSP.cpp
	#main.cpp
	v4l2Device_custom.cpp
)

set(HDR_FILES
	v4l2Device_custom.h
)

# v4l2wrapper
include_directories(${CMAKE_SOURCE_DIR}/v4l2cpp/inc)
find_library(
	V4L2WRAPPER_LIBRARY 
	NAMES	libv4l2wrapper.a 
	HINTS	./v4l2cpp
)
	
#Thread
find_package (Threads)

# LOG4CPP
find_path(LOG4CPP_INCLUDE_DIR log4cpp/Category.hh)
if (LOG4CPP_INCLUDE_DIR)
        message(STATUS "Log4Cpp available")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_LOG4CPP")
	include_directories(${LOG4CPP_INCLUDE_DIR}) 

	find_library(LOG4CPP_LIBRARY log4cpp)

	SET(CPACK_DEBIAN_PACKAGE_DEPENDS ${CPACK_DEBIAN_PACKAGE_DEPENDS}liblog4cpp5-dev,)
endif (LOG4CPP_INCLUDE_DIR)

# Live555 
include_directories(/usr/local/include/liveMedia)
include_directories(/usr/local/include/BasicUsageEnvironment)
include_directories(/usr/local/include/groupsock)
include_directories(/usr/local/include/UsageEnvironment)

find_library(
	libliveMedia 
	NAMES	libliveMedia.a
	HINTS	/usr/local/lib
)
find_library(
	libBasicUsageEnvironment 
	NAMES	libBasicUsageEnvironment.a 
	HINTS	/usr/local/lib
)
find_library(
	libgroupsock 
	NAMES	libgroupsock.a
	HINTS	/usr/local/lib
)
find_library(
	libUsageEnvironment 
	NAMES	libUsageEnvironment.a 
	HINTS	/usr/local/lib
)

set(LIB
	 ${V4L2WRAPPER_LIBRARY} 
	 ${CMAKE_THREAD_LIBS_INIT}
	 ${LOG4CPP_LIBRARY} 
	 ${libliveMedia}
	 ${libBasicUsageEnvironment}
	 ${libgroupsock}
	 ${libUsageEnvironment}
	 -lpthread
	 -lm
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES})
target_link_libraries(${PROJECT_NAME} ${LIB})
