cmake_minimum_required(VERSION 3.6)
project(VoiceActivityDetection)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        inc/VAD.h
        inc/VADImp.h
        inc/ThresholdFinder.h
        inc/EnergyBasedDetector.h
        inc/ResultPlotter.h
        inc/SingleFrameEnergyFinder.h
        inc/SohnsDetector.h
        src/main.cpp
        src/VAD.cpp
        src/VADImp.cpp
        src/ThresholdFinder.cpp
        src/EnergyBasedDetector.cpp
        src/ResultPlotter.cpp
        src/SingleFrameEnergyFinder.cpp
        src/SohnsDetector.cpp )

add_executable(VoiceActivityDetection ${SOURCE_FILES})

include_directories(/home/paulina/github/VoiceActivityDetection/aquila/include)

target_link_libraries(VoiceActivityDetection
        /home/paulina/github/VoiceActivityDetection/aquila/lib/libAquila.a
        /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/lib/libOoura_fft.a)

