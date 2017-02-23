//
// Created by paulina on 21.02.17.
//

#ifndef VOICEACTIVITYDETECTION_SINGLEFRAMEENERGYFINDER_H
#define VOICEACTIVITYDETECTION_SINGLEFRAMEENERGYFINDER_H


#include <aquila/source/WaveFile.h>

class SingleFrameEnergyFinder {
private:
    double singleFrameEnergy;
    unsigned int samplesPerFrame;
    unsigned int commonSamples;
public:
    SingleFrameEnergyFinder();
    virtual ~SingleFrameEnergyFinder();
    double countSingleFrameEnergy(Aquila::WaveFile wav,size_t frameNumber);
    unsigned int getSamplesPerFrame();
    unsigned int getCommonSamples();
    void setSamplesPerFrame(unsigned int samplesAmount);

};


#endif //VOICEACTIVITYDETECTION_SINGLEFRAMEENERGYFINDER_H
