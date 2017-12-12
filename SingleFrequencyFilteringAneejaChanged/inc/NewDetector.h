//
// Created by paulina on 25.11.17.
//

#ifndef VOICEACTIVITYDETECTION_NEWDETECTOR_H
#define VOICEACTIVITYDETECTION_NEWDETECTOR_H

#include <vector>
#include <aquila/source/SignalSource.h>

using namespace std;
using namespace Aquila;

/***
 * This class is really similar to this from Aneeja's article, but it
 * was changed in some ways by prof. Makowski.
 * List of changed things:
 * 1. Implementation of single-pole filter
 * 2. Computating threshold
 * 3.
 */

//TODO: THIS IS A COPYPASTA FROM ANEEJA - CHANGE THIS IN PROPER WAY!!!
class NewDetector {
private:
    double _samplingFrequency;
    vector<int> result;
    double _windowSize;
public:
    NewDetector();
    virtual ~NewDetector();
    void detect(Aquila::SignalSource& wav);

    SignalSource differenceSignal(const SignalSource &wav);

    vector<complex<SampleType>> MultipyByComplexSinusoid(const SignalSource& wav, int frequency);

    vector<complex<double>> countFilterOutput(vector<complex<SampleType>> &wav);

    vector<SampleType> countEnvelope(vector<complex<double>> &wav);

    vector<SampleType> countSingleSFFEnvelope(SignalSource &wav, int normalizedFrequency);

    double countWeightValue(vector<SampleType> envelope);

    vector<SampleType> scaleSignal(vector<SampleType> wavEnvelope, double weight);

    SignalSource addGaussianNoiseToSignal(const SignalSource& signal, double noiseMultiplication);

    vector<SampleType> countSFFEnvelopesForFrequencies(SignalSource &source, int beginFrequency, int endFrequency, int interval);

    double countThresholdBeta(vector<SampleType> delta);

    double countDynamicRange(SignalSource source);

    vector<double> countSignalEnergyPerFrame(SignalSource source);

    double countSingleFrameEnergy(Frame &frame);

    double countWindowSize(double ro);

    vector<SampleType> averageVector(vector<SampleType>& vector, double size);

    vector<short> makeDecisionAtSampleLevel(vector<SampleType>& averagedVector, double threshold);

    vector<short> smoothDecision(vector<short>& decision, double windowSize);

    vector<short> makeDecisionAtFrameLevel(const SignalSource& delta, double threshold);

    SignalSource vectorToSignalSource(vector<SampleType> vectorToConvert);

    vector<double> smoothSignal(const vector<SampleType>& signal, int loops);

    vector<double>
    countDensityForPositiveValues(vector<SampleType> vectorToCount, unsigned long amountOfDensityPoints, double maxDelta);

    double countThresholdTheta(vector<SampleType> vector);

    SignalSource addGaussianNoiseToSignal2(SignalSource &source);
};


#endif //VOICEACTIVITYDETECTION_NEWDETECTOR_H
