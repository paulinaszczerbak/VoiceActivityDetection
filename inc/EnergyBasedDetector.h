/*
// Created by paulina on 06.02.17.
algorytm VAD bazujacy na energii sygnalu
*/

#ifndef VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H
#define VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H

#include "../aquila/include/aquila/source/WaveFile.h"

#include "ThresholdFinder.h"
#include "WAVFileSetterImp.h"

class EnergyBasedDetector : public WAVFileSetterImp, public ThresholdFinder{
private:
    //float singleFrameEnergy;
    float singleFrameEnergy;
    int samplesPerFrame;
    int commonSamples;
    int framesAmount;
    //lista lub tablica z wynikami detekcji
    bool result[16000];
public:
    EnergyBasedDetector();
    virtual ~EnergyBasedDetector();
    float countSingleFrameEnergy(int frameNumber);
    float getSingleFrameEnergy();
    void detect();
    void setFramesAmount();
    int getFramesAmount();
};


#endif //VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H
