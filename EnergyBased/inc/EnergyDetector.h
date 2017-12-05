//
// Created by paulina on 01.12.17.
//

#ifndef VOICEACTIVITYDETECTION_ENERGYDETECTOR_H
#define VOICEACTIVITYDETECTION_ENERGYDETECTOR_H

#include <aquila/global.h>
#include <aquila/source/SignalSource.h>

using namespace std;
using namespace Aquila;

class EnergyDetector {
public:
    void detect(SignalSource& wav);

    int countThreshold100firstms();
};


#endif //VOICEACTIVITYDETECTION_ENERGYDETECTOR_H
