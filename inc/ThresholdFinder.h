/*
// Created by paulina on 06.02.17.
Klasa do ustalania poczatkowego progu detekcji
*/

#ifndef VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
#define VOICEACTIVITYDETECTION_THRESHOLDFINDER_H


#include <aquila/source/WaveFile.h>

class ThresholdFinder {
private:
    double threshold;
public:
    ThresholdFinder();
    virtual ~ThresholdFinder();
    double getThreshold();
    void initialThreshold100ms(Aquila::WaveFile wav);

};


#endif //VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
