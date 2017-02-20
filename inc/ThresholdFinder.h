/*
// Created by paulina on 06.02.17.
Klasa do ustalania poczatkowego progu detekcji
*/

#ifndef VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
#define VOICEACTIVITYDETECTION_THRESHOLDFINDER_H


#include <aquila/source/WaveFile.h>

class ThresholdFinder {
private:
    float threshold;
public:
    ThresholdFinder();
    virtual ~ThresholdFinder();
    float getThreshold();
    void countThreshold(Aquila::WaveFile wav);
    //void setThreshold(float threshold);
};


#endif //VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
