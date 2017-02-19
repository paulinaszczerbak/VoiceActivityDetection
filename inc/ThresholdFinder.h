/*
// Created by paulina on 06.02.17.
Klasa do ustalania poczatkowego progu detekcji
*/

#ifndef VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
#define VOICEACTIVITYDETECTION_THRESHOLDFINDER_H


class ThresholdFinder {
private:
    float threshold;
public:
    ThresholdFinder();
    float getThreshold();
    void setThreshold(float threshold);
};


#endif //VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
