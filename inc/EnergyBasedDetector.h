/*
// Created by paulina on 06.02.17.
algorytm VAD bazujacy na energii sygnalu
*/

#ifndef VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H
#define VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H

#include "../aquila/include/aquila/source/WaveFile.h"

#include "ThresholdFinder.h"
#include "SingleFrameEnergyFinder.h"
#include "VADImp.h"


//class EnergyBasedDetector : public WAVFileSetterImp, public ThresholdFinder{
class EnergyBasedDetector : public ThresholdFinder,
                            public SingleFrameEnergyFinder,
                            public VADImp{
private:

public:
    EnergyBasedDetector();
    virtual ~EnergyBasedDetector();
    //double countSingleFrameEnergy(Aquila::WaveFile wav, size_t frameNumber);
    //double getSingleFrameEnergy();
    void detect(Aquila::WaveFile wav);
    //void setFramesAmount(Aquila::WaveFile wav);
    //size_t getFramesAmount();
};


#endif //VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H
