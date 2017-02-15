/*
// Created by paulina on 06.02.17.
algorytm VAD bazujacy na energii sygnalu
*/

#ifndef VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H
#define VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H


class EnergyBasedDetector {
private:
    float singleFrameEnergy;
public:
    EnergyBasedDetector();
    void countSingleFrameEnergy(int frameNumber);
    float getSingleFrameEnergy();
};


#endif //VOICEACTIVITYDETECTION_ENERGYBASEDDETECTOR_H
