//
// Created by paulina on 07.07.17.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include "../inc/SFFDetector.h"

SFFDetector::SFFDetector(std::string filename) {
    _signal = new Signal(filename);

//    _signalOriginal = new Aquila::WaveFile(filename);
//    _samplesCount=_signalOriginal->getSamplesCount();

//    _samplesOriginal = new Aquila::SampleType[_samplesCount];
//    _samplesAfterFiltering = new Aquila::SampleType[_samplesCount];
//    _samplesSpectrum = new Aquila::SampleType[_samplesCount];
//
//    //kopiuje probki do 3 roznych tablic
//    std::copy(_signalOriginal->toArray(),
//              _signalOriginal->toArray()+_samplesCount,
//              _samplesOriginal);
//    std::copy(_signalOriginal->toArray(),
//              _signalOriginal->toArray()+_samplesCount,
//              _samplesAfterFiltering);
//    std::copy(_signalOriginal->toArray(),
//              _signalOriginal->toArray() +_samplesCount,
//              _samplesSpectrum);

}

SFFDetector::Signal::Signal(std::string filename) {
    signalOriginal = new Aquila::WaveFile(filename);
    samplesCount = signalOriginal->getSamplesCount();
    samplesOriginal = new Aquila::SampleType[samplesCount];
    samplesNoised = new Aquila::SampleType[samplesCount];
    samplesDifferentationed = new Aquila::SampleType[samplesCount];
    samplingFrequency = signalOriginal->getSampleFrequency();

    std::copy(signalOriginal->toArray(),
              signalOriginal->toArray()+samplesCount,
              samplesOriginal);
    //czy moze lepiej mamcpy?
    std::copy(signalOriginal->toArray(),
              signalOriginal->toArray()+samplesCount,
              samplesNoised);
    std::copy(signalOriginal->toArray(),
              signalOriginal->toArray()+samplesCount,
              samplesDifferentationed);
}

SFFDetector::Envelope::Envelope() {
    this->singlePoleModule=0.97;
    this->firstThreshold=0.15;
    
}


void SFFDetector::printSamples() {
    std::cout<<_signal->samplesOriginal[5]<<std::endl;
    addGaussNoise(5);
    std::cout<<_signal->samplesOriginal[5]<<std::endl;
    std::cout<<_signal->samplesNoised[5]<<std::endl;
}

/// funkcja dodajaca szum do sygnalu
/// \param signal
/// \param noiseMult
void SFFDetector::addGaussNoise(double noiseMult) {
    //zmienne lokalne do wygenerowania szumu
    clock_t  timer;
    //RAND_MAX - maksymalna wartosc zwrocona przez rand()
    long centr = RAND_MAX/2;
    long random1(0), random2(0);

    timer = clock();
    srand(timer);
    for (long i = 0; i <_signal->samplesCount ; i++) {
        random1=0;
        for (int j = 0; j < 16 ; j++) {
            random2 = rand();
            random1 += random2 - centr;
        }
        //dodatkowe dzielenie w przypadku kompilatora 64-bitowego
        random1 /= 65536;
        random1 /= 8;
        _signal->samplesNoised[i] = _signal->samplesOriginal[i] + noiseMult * random1;
    }
}

///funkcja do obliczania gestosci dla pozytywnych wartosci
/// oblicza wspolczynnik normowania
/// \param sPosNb
/// \param max
void SFFDetector::densityForPositiveValues(double* VAETab,double max, double* VAEDensity, short sPosNb ) {
    double normFactor;
    short temp;

    normFactor = (sPosNb-1)/max;
    memset(VAEDensity, 0, sPosNb*sizeof(double));

    for (int i = 0; i <_signal->samplesCount ; ++i) {
        temp = (long) floor(normFactor*VAETab[i]+0.5);
        if (temp <= sPosNb){
            VAEDensity[temp]++;
        }
    }
    for (int j = 0; j < sPosNb ; ++j) {
        VAEDensity[j] /= _signal->samplesCount;
    }
}

/// funckcja do obliczania czestotliwosci obwiedni
/// \param frequency - czestotliwosc
void SFFDetector::singleFrequencyEnvelope(double frequency) {
    double filterFactor1, filterFactor2;
    double om, max, threshold1, threshold2, temp, distance;
    double mod;
    long length;

    om = 2*PI*frequency/_signal->samplingFrequency;

}

