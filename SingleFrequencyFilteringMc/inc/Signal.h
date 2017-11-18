//
// Created by paulina on 16.09.17.
//

#ifndef VOICEACTIVITYDETECTION_SIGNAL_H
#define VOICEACTIVITYDETECTION_SIGNAL_H


#include <aquila/source/WaveFile.h>

using namespace std;

class Signal {

public:
    Signal(string filename);
    virtual ~Signal();

    Aquila::WaveFile* signalOriginal;
    unsigned int samplesCount;
    vector<Aquila::SampleType> samplesOriginal;
    Aquila::FrequencyType samplingFrequency;
    vector<Aquila::SampleType> samplesNoised;
    vector<Aquila::SampleType> samplesDifferential;
};


#endif //VOICEACTIVITYDETECTION_SIGNAL_H
