# Install script for directory: /home/issuh/Project/Study/STL_study

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/issuh/Project/Study/STL_study/build/src/2-1/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/2-3/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/2-4/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/2-7/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/2-8/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/2-9/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/3-1/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/3-3/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/3-4/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/3-5/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/3-6/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/3-7/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/3-8/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/3-10/cmake_install.cmake")
  include("/home/issuh/Project/Study/STL_study/build/src/4-1/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/issuh/Project/Study/STL_study/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
