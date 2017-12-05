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
    double _windowSize;
public:
    Detector();

    virtual ~Detector();

    void detect(Aquila::SignalSource &wav);

    SignalSource differenceSignal(const SignalSource &wav);

    vector<complex<SampleType>> MultipyByComplexSinusoid(const SignalSource &wav, int frequency);

    vector<complex<double>> countFilterOutput(vector<complex<SampleType>> &wav);

    vector<SampleType> countEnvelope(vector<complex<double>> &wav);

    vector<SampleType> countSFFEnvelope(SignalSource &wav, int normalizedFrequency);

    double countWeightValue(vector<SampleType> envelope);

    vector<SampleType> scaleSignal(vector<SampleType> wavEnvelope, double weight);

    SignalSource addGaussianNoiseToSignal(const SignalSource& signal);

    vector<SampleType>
    countSFFEnvelopesForFrequencies(SignalSource &source, int beginFrequency, int endFrequency, int interval);

    double countThreshold(vector<SampleType> delta, double smoothingWindowSize);

    double countDynamicRange(SignalSource source);

    vector<double> countSignalEnergyPerFrame(SignalSource source);

    double countSingleFrameEnergy(Frame &frame);

    double countWindowSize(double ro);

    vector<SampleType> averageVector(vector<SampleType> &vector, double size);

    vector<short> makeDecisionAtSampleLevel(vector<SampleType> &averagedVector, double threshold);

    vector<short> smoothDecision(vector<short> &decision, double windowSize);

    vector<short> makeDecisionAtFrameLevel(const SignalSource &delta, double threshold);

    SignalSource vectorToSignalSource(vector<SampleType> vectorToConvert);

    SignalSource addGaussianNoiseToSignalTimer(SignalSource &signal, double multiplication);

    vector<SampleType> smoothSignal(vector<SampleType>& signal, int loops);
};
#endif //VOICEACTIVITYDETECTION_DETECTOR_H
