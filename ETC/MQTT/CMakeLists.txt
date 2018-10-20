# 요구 CMake 최소 버전
CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
 
# 프로젝트 이름 및 버전
PROJECT (MQTT)

# 공통 컴파일러
#SET ( CMAKE_C_COMPILER g++)
set ( CMAKE_CXX_STANDARD 11)

# 공통 컴파일 옵션, 링크 옵션
ADD_COMPILE_OPTIONS (-static -g -Wall )
SET ( CMAKE_EXE_LINKER_FLAGS  "-Wl,--gc-sections -Wreturn-local-addr")
 
# "Debug" 형상 한정 컴파일 옵션, 링크 옵션
SET ( CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
SET ( CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS" )
 
# "Release" 형상 한정 컴파일 옵션, 링크 옵션
SET ( CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS" )
SET ( CMAKE_EXE_LINKER_FLAGS_RELEASE "-DRELEASE -DLINKER_FLAGS" )

if (NOT MOSQUITTO_INCLUDE_DIR)
  find_path(MOSQUITTO_INCLUDE_DIR mosquitto.h)
endif()


if (NOT MOSQUITTO_LIBRARY)
  find_library( MOSQUITTO_LIBRARY NAMES mosquitto)
endif()

include_directories(${MOSQUITTO_INCLUDE_DIR})

SET(SOURCES
    src/main.cpp
)

SET(HEADER
    src/mqtt.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER})
target_link_libraries(${PROJECT_NAME} ${MOSQUITTO_LIBRARY})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "MQTT")
