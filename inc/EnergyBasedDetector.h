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
class EnergyBasedDetector :
                            public SingleFrameEnergyFinder,
                            public VADImp{
private:
    ThresholdFinder *threshold;

public:
    EnergyBasedDetector();
    virtual ~EnergyBasedDetector();
    void detect(Aquila::WaveFile wav);

    Aquila::SignalSource addGaussianNoiseToSignal(Aquila::WaveFile file);
};


#endif //VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H
