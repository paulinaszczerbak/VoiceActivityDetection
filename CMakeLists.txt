cmake_minimum_required(VERSION 3.6)
project(VoiceActivityDetection)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        inc/VAD.h
        inc/VADImp.h
        inc/WAVReader.h
        inc/WAVReaderImp.h
        src/main.cpp
        src/VAD.cpp
        src/VADImp.cpp
        src/WAVReader.cpp
        src/WAVReaderImp.cpp
        ThresholdFinder.cpp ThresholdFinder.h EnergyBasedDetector.cpp EnergyBasedDetector.h)

add_executable(VoiceActivityDetection ${SOURCE_FILES})

include_directories(/home/paulina/github/VoiceActivityDetection/aquila/include)

target_link_libraries(VoiceActivityDetection /home/paulina/github/VoiceActivityDetection/aquila/lib/libAquila.a)

