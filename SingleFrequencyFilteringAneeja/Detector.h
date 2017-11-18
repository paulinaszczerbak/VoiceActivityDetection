//
// Created by paulina on 17.11.17.
//

#ifndef VOICEACTIVITYDETECTION_DETECTOR_H
#define VOICEACTIVITYDETECTION_DETECTOR_H

#include <vector>
#include <aquila/source/SignalSource.h>

using namespace std;
using namespace Aquila;

class Detector {
private:
    double _samplingFrequency;
    vector<int> result;
public:
    Detector();
    virtual ~Detector();
    void detect(Aquila::SignalSource& wav);

    SignalSource differenceSignal(const Aquila::SignalSource &wav);

    vector<complex<SampleType>> MultipyByComplexSinusoid(const Aquila::SignalSource& wav, int frequency);

    vector<complex<double>> countFilterOutput(vector<complex<SampleType>> &wav);

    vector<SampleType> countSignalEnvelope(vector<complex<double>> &wav);
};


#endif //VOICEACTIVITYDETECTION_DETECTOR_H
