# 요구 CMake 최소 버전
CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
 
# 프로젝트 이름 및 버전
PROJECT (MQTT_Sub)

# 공통 컴파일러
#SET ( CMAKE_C_COMPILER g++)
set ( CMAKE_CXX_STANDARD 11)

# 공통 컴파일 옵션, 링크 옵션
ADD_COMPILE_OPTIONS ( -g -Wall )
SET ( CMAKE_EXE_LINKER_FLAGS  "-static -Wl,--gc-section2s -Wreturn-local-addr")
 
# "Debug" 형상 한정 컴파일 옵션, 링크 옵션
SET ( CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
SET ( CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS" )
 
# "Release" 형상 한정 컴파일 옵션, 링크 옵션
SET ( CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS" )
SET ( CMAKE_EXE_LINKER_FLAGS_RELEASE "-DRELEASE -DLINKER_FLAGS" )

include_directories(/usr/local/include)
link_directories(/usr/local/include)

SET(SOURCES
    src/main.cpp
    src/mqtt.cpp
)

SET(HEADER
    src/mqtt.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER})
target_link_libraries(${PROJECT_NAME -lmosquitto})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "MQTT_Sub")
