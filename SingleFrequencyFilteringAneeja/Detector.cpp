//
// Created by paulina on 17.11.17.
//

#include <iostream>
#include "Detector.h"
using namespace Aquila;


Detector::Detector() {

}

Detector::~Detector() {

}


/***
 * Detect if there is speech or nonspeech
 * @param wav - detecting signal
 */
void Detector::detect(SignalSource& wav) {
    _samplingFrequency = wav.getSampleFrequency();
    //difference the signal
    SignalSource wavDifferenced = differenceSignal(wav);

    int normalizedFrequency = 3200;
    //multiply signal x(n) by a complex sinusoid of a given normalized frequency wk
    vector<complex<SampleType>> wavMultipliedByComplexSinusoid = MultipyByComplexSinusoid(wavDifferenced, normalizedFrequency);

    //count output yk(n) = -r*yk(n-1) +xk(n)
    vector<complex<double>> wavFilterOutput= countFilterOutput(wavMultipliedByComplexSinusoid);

    //count envelope
    vector<SampleType> wavEnvelope = countSignalEnvelope(wavFilterOutput);

}

/***
 * Function to calculate signal denoted by x(n) = s(n) - s(n-1)
 * @param wav - signal to difference
 * @return
 */
Aquila::SignalSource Detector::differenceSignal(const Aquila::SignalSource &wav) {
    vector<SampleType> wavVector(wav.begin(), wav.end());
    vector<SampleType> wavDifferenced;
    wavDifferenced.push_back(wavVector[0]);
    for (vector<SampleType>::iterator it=wavVector.begin()+1; it!=wavVector.end(); ++it){
        wavDifferenced.push_back(*it - *(it-1));
    }

    return SignalSource(wavDifferenced, wav.getSampleFrequency());
}


/**
 * multiplies signal by complex sinusoid
 * @param source - wav signal
 * @param frequency - signal sampling frequency
 * @return
 */
vector<complex<SampleType>> Detector::MultipyByComplexSinusoid(const Aquila::SignalSource& wav, int normalizedFrequency) {

    vector<SampleType> wavVector(wav.begin(), wav.end());
    vector<complex<SampleType>> result;
    //complex sinusoid
    const double pi = acos(-1);
    const complex<double> j(0, 1);


    double omega_k = (2*pi*normalizedFrequency)/wav.getSampleFrequency();
    for (vector<SampleType>::iterator it=wavVector.begin(); it!=wavVector.end(); ++it){
        long index = std::distance(wavVector.begin(), it);
        //exp(j*sr_omega_k*n)
        result.push_back(*it*exp(j*omega_k*(double)index));
    }

    return result;
}

/***
 * Single-pole filter has a pole on the real axis at a distance of r from the origin.
 * the location of the root is at z=-r in the z-plane, which corresponds to half the sampling
 * frequency fs/2
 * The output of the filter is given by
 * yk(n) = -r*yk(n-1) +xk(n)
 * @param wav - vector to filter
 * @return
 */
vector<complex<double>> Detector::countFilterOutput(vector<complex<SampleType>> &wav) {
    double root = 0.97;

    vector<complex<double>> output;
    //y(0)=0
    output.push_back((0.0,0.0));

    //iterating starts at index=1, because we use output[index-1]
    for (vector<complex<SampleType>>::iterator signalSample=wav.begin()+1; signalSample!=wav.end(); ++signalSample){
        unsigned long currentIndex = (unsigned long)distance(wav.begin(), signalSample);
        output.push_back(output.at(currentIndex-1) *(-root) + *signalSample);
    }


    return output;
}

/***
 * Function counting values for signal's envelope
 * @param complexSignal - signal with complex samples
 * @return
 */
vector<SampleType> Detector::countSignalEnvelope(vector<complex<double>> &complexSignal) {
    vector<SampleType> envelope;
    for (vector<complex<SampleType>>::iterator signalSample=complexSignal.begin(); signalSample!=complexSignal.end(); ++signalSample){
        unsigned long currentIndex = (unsigned long)distance(complexSignal.begin(), signalSample);
        envelope.push_back(sqrt((*signalSample).real()*(*signalSample).real() + (*signalSample).imag()*(*signalSample).imag()));
        cout<<envelope.at(currentIndex)<<" ";
    }
    return envelope;
}
