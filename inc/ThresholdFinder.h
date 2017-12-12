/*
// Created by paulina on 06.02.17.
Klasa do ustalania poczatkowego progu detekcji
*/

#ifndef VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
#define VOICEACTIVITYDETECTION_THRESHOLDFINDER_H


#include <aquila/source/WaveFile.h>
#include "SingleFrameEnergyFinder.h"

class ThresholdFinder {
private:
    double threshold;
    double Emin;
    double Emax;
    double scalingFactor;
    SingleFrameEnergyFinder frameEn;
    double initialValue;
    double delta;
public:
    ThresholdFinder();
    virtual ~ThresholdFinder();
    double getThreshold();
    void calculateThreshold100ms(Aquila::SignalSource wav);
    void calculateThresholdEminEmax(Aquila::WaveFile wav, size_t currentFrameNumber);

};


#endif //VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
