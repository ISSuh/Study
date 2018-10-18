# 요구 CMake 최소 버전
CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
 
# 프로젝트 이름 및 버전
PROJECT (STL_Study)

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


SET (SAMPLES 2-1; 2-3; 2-4; 2-7; 2-8; 2-9;
             3-1; 3-3; 3-4; 3-5; 3-6; 3-7; 3-8; 3-10;
             4-1;)

foreach(SAMPLE ${SAMPLES})
    add_subdirectory(src/${SAMPLE})
endforeach()