//
// Created by paulina on 17.11.17.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include "../inc/Detector.h"
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
    double weight(0);
    int normalizedFrequency = 3200;
    //add some gaussian noise
    SignalSource wavNoised = addGaussianNoiseToSignal(wav);
    //todo: count SFFEnvelopes for 185 frequencies 300-4000Hz by 20Hz
    int beginFrequency = 300;
    int endFrequency = 4000;
    int interval = 20;
    vector<SampleType> meanFromSquareOfEnvelopes = countSFFEnvelopesForFrequencies(wavNoised, 300, 4000, 20);

//    //count Single Frequency Filtered envelope
//    vector<SampleType> SFFEnvelope = countSFFEnvelope(wavNoised, normalizedFrequency);
//    //count weight value for specefic normalizedFrequency
//    weight = countWeightValue(SFFEnvelope);
//    //scale envelope
//    vector<SampleType> weightedComponentEnvelope = scaleSignal(SFFEnvelope, weight);

    //todo: count the mean of the square of the weighted component envelopes computed across frequency
//    vector<SampleType> squareOfScaledEnvelope = countSquareOfEachElement(wavEnvelope, weight);

    //writing to file to plot results
//    system("touch result2ToPlot");
//    //otwieram plik do zapisu
//    ofstream file("result2ToPlot");
//    if(file){
//        for (size_t i = 0; i< weightedComponentEnvelope.size() ; i++) {
//            file << weightedComponentEnvelope[i] << endl;
//        }
//        file.close();
//    } else{
//        cout<<"BLAD: nie mozna otworzyc pliku"<<endl;
//    }

}

/***
 * counting Single Frequency Filtering envelope for specific frequency
 * @param wav - signal to process
 * @param normalizedFrequency - specific frequency which will be used to complex sine
 * @return
 */
vector<SampleType> Detector::countSFFEnvelope(SignalSource &wav, int normalizedFrequency) {
    //todo: add noise to signal
    //difference the signal
    SignalSource wavDifferenced = differenceSignal(wav);

    //multiply signal x(n) by a complex sinusoid of a given normalized frequency wk
    vector<complex<SampleType>> wavMultipliedByComplexSinusoid = MultipyByComplexSinusoid(wavDifferenced, normalizedFrequency);

    //count output yk(n) = -r*yk(n-1) +xk(n)
    vector<complex<double>> wavFilterOutput= countFilterOutput(wavMultipliedByComplexSinusoid);

    //count envelope
    vector<SampleType> wavEnvelope = countEnvelope(wavFilterOutput);

    return wavEnvelope;
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
vector<complex<SampleType>> Detector::MultipyByComplexSinusoid(const SignalSource& wav, int normalizedFrequency) {

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
//    const double root = 0.97; //prof.
    const double root = 0.99;   //article

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
vector<SampleType> Detector::countEnvelope(vector<complex<double>> &complexSignal) {
    vector<SampleType> envelope;
    for (vector<complex<SampleType>>::iterator signalSample=complexSignal.begin(); signalSample!=complexSignal.end(); ++signalSample){
        unsigned long currentIndex = (unsigned long)distance(complexSignal.begin(), signalSample);
        envelope.push_back(sqrt((*signalSample).real()*(*signalSample).real() + (*signalSample).imag()*(*signalSample).imag()));
//        cout<<envelope.at(currentIndex)<<" ";
    }
    //normalize envelope values

    return envelope;
}

double Detector::countWeightValue(vector<SampleType> envelope ) {
    //sort envelope values to get 20% of the lowest (20% from the beginning)
    sort(envelope.begin(), envelope.end());

    //get 20% first samples
    int amountOfSamples = (int)(envelope.size()*0.2);
    vector<SampleType> splitedEnvelope(envelope.begin(), envelope.begin()+amountOfSamples);

    //mean of the lower 20% of the values of the envelope
    double average = accumulate( splitedEnvelope.begin(), splitedEnvelope.end(), 0.0)/splitedEnvelope.size();

    return 1/average;
}

vector<SampleType> Detector::scaleSignal(vector<SampleType> wavEnvelope, double weight) {
    //multiply vector by scalar
    std::transform(wavEnvelope.begin(), wavEnvelope.end(), wavEnvelope.begin(),
                   std::bind1st(std::multiplies<SampleType>(), weight));
    return wavEnvelope;
}

/***
 * [Note: Seeding from std::random_device is a good practice to get into;
 * if you use the current time as a seed, you can end up with the same seed
 * value across multiple generators (e.g. when initialising several generators
 * in a very short period of time).
 * std::random_device will obtain entropy from the system, if available
 * @param signal
 * @return
 */
SignalSource Detector::addGaussianNoiseToSignal(SignalSource signal) {

    vector<SampleType> noised(signal.begin(), signal.end());
    // Define random generator with Gaussian distribution
    const double mean = 0.0;
    const double stddev = 0.1;

    auto dist = std::bind(std::normal_distribution<double>{mean, stddev},
                          std::mt19937(std::random_device{}()));

    // Add Gaussian noise
    for (auto& x : noised) {
        x = x + dist();
    }

    return SignalSource(noised, signal.getSampleFrequency());
}

vector<SampleType>
Detector::countSFFEnvelopesForFrequencies(SignalSource &source, int beginFrequency, int endFrequency, int interval) {
    double weight(0);
    //zapisuje do tego wektora sume kwadratow probek
    // - po kazdym policzeniu obwiedni dodaje kolejne probki (wlasciwie to ich kwadraty)
    vector<SampleType> meanSquareEnvelope;

    for (int frequency = beginFrequency; frequency <endFrequency; frequency=frequency+20) {
        //count Single Frequency Filtered envelope
        vector<SampleType> SFFEnvelope = countSFFEnvelope(source, frequency);
        //count weight value for specific normalizedFrequency
        weight = countWeightValue(SFFEnvelope);
        //scale envelope
        vector<SampleType> weightedComponentEnvelope = scaleSignal(SFFEnvelope, weight);

    }


    return meanSquareEnvelope;
}

