# Install script for directory: /home/dongchen/dynapse/caer/modules

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
  include("/home/dongchen/dynapse/caer/modules/backgroundactivityfilter/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/cameracalibration/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/frameenhancer/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/framestatistics/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/ini/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/misc/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/statistics/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/visualizer/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/meanratefilter/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/synapsereconfig/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/fpgaspikegen/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/softspikegen/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/poissonspikegen/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/reservoir/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/netparser/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/nullhopinterface/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/localfiltdownsample/cmake_install.cmake")
  include("/home/dongchen/dynapse/caer/modules/dsnn/cmake_install.cmake")

endif()

