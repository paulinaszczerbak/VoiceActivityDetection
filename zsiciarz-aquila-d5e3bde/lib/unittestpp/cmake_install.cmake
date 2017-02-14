# Install script for directory: /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/paulina/github/VoiceActivityDetection/aquila")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/libUnitTest++.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++" TYPE FILE FILES
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TestList.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/DeferredTestResult.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/Config.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/AssertException.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TestResults.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/ReportAssert.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TimeHelpers.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/ReportAssertImpl.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/ExecuteTest.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TestDetails.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/MemoryOutStream.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/DeferredTestReporter.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TimeConstraint.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/UnitTestPP.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TestReporterStdout.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TestRunner.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/UnitTest++.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TestReporter.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TestMacros.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/CurrentTest.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/CheckMacros.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/HelperMacros.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/ExceptionMacros.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/Checks.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/Test.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/TestSuite.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/XmlTestReporter.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/CompositeTestReporter.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++/Posix" TYPE FILE FILES
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/Posix/TimeHelpers.h"
    "/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/unittestpp/UnitTest++/Posix/SignalTranslator.h"
    )
endif()

