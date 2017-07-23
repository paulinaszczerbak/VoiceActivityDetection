//
// Created by paulina on 07.07.17.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include "../inc/SFFDetector.h"

SFFDetector::SFFDetector(std::string filename) {
    _signal = new Signal(filename);
    _envelope = new Envelope(_signal->samplesCount);

}

SFFDetector::Signal::Signal(std::string filename) {
    signalOriginal = new Aquila::WaveFile(filename);
    samplesCount = signalOriginal->getSamplesCount();
    //samplesOriginal = new Aquila::SampleType[samplesCount];
    samplesOriginal = (Aquila::SampleType *) malloc(samplesCount * sizeof(Aquila::SampleType));
    samplesNoised = new Aquila::SampleType[samplesCount];
    samplesDifferential = new Aquila::SampleType[samplesCount];
    samplingFrequency = signalOriginal->getSampleFrequency();

    std::copy(signalOriginal->toArray(),
              signalOriginal->toArray()+samplesCount,
              samplesOriginal);
    //czy moze lepiej mamset?
    std::memset(samplesNoised, 0, samplesCount*sizeof(Aquila::SampleType));
//    std::copy(signalOriginal->toArray(),
//              signalOriginal->toArray()+samplesCount,
//              samplesNoised);
    std::memset(samplesDifferential, 0, samplesCount*sizeof(Aquila::SampleType));
//    std::copy(signalOriginal->toArray(),
//              signalOriginal->toArray()+samplesCount,
//              samplesDifferential);
}

SFFDetector::Signal::~Signal() {
    delete signalOriginal;
    delete samplesOriginal;
    delete samplesNoised;
    delete samplesDifferential;
}

SFFDetector::Envelope::Envelope(int samplesCount) {
    this->samplesCount=samplesCount;
    singleFrequencyEnvelope = (double *) malloc(samplesCount * sizeof(double));
    this->singlePoleModule=0.97;
    this->firstThreshold=0.15;
    this->differBef = true;

    factorXi = (double *) malloc(samplesCount * sizeof(double));
    factorXr = (double *) malloc(samplesCount * sizeof(double));

    memset(singleFrequencyEnvelope, 0, samplesCount );
    memset(factorXi,0, samplesCount );
    memset(factorXr,0, samplesCount );

}

SFFDetector::Envelope::~Envelope() {
    delete singleFrequencyEnvelope;
    delete factorXi;
    delete factorXr;
}

void SFFDetector::printSamples() {

    addGaussNoise(0.0001);

    if(_envelope->differBef){
        for (int i = 1; i <_signal->samplesCount ; i++) {
            _signal->samplesDifferential[i] = _signal->samplesNoised[i] - _signal->samplesNoised[i-1];

        }
    }
    else{
        for (int i = 0; i < _signal->samplesCount ; i++) {
            _signal->samplesDifferential[i] = _signal->samplesNoised[i];
        }
    }

    singleFrequencyEnvelope(4000);

    system("touch result2ToPlot");
    //otwieram plik do zapisu
    std::ofstream file("result2ToPlot");
    int xValue(0);
    int arraySize = sizeof(_envelope->singleFrequencyEnvelope)/sizeof(_envelope->singleFrequencyEnvelope[0]);
    if(file){
        for (size_t i = 0; i < _signal->samplesCount ; i++) {
            file << _envelope->singleFrequencyEnvelope[i] << std::endl;
        }
        file.close();
    } else{
        std::cout<<"BLAD: nie mozna otworzyc pliku"<<std::endl;
    }
}

/// funkcja dodajaca szum do sygnalu
/// \param signal
/// \param noiseMult - mnoznik szumu
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
void SFFDetector::densityForPositiveValues(double* VAETab,double max,
                                           double* VAEDensity, short sPosNb ) {
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
    double filterFactorCos(0), filterFactorSin(0);
    double normalizedFrequency(0), max(0), threshold1(0),
            threshold2(0), temp(0), distance(0), module(0);
    long sigLength(0);

    sigLength=_signal->samplesCount;

    //wzor na omegak z artykulu
    normalizedFrequency = 2*PI*frequency/_signal->samplingFrequency;
    module = _envelope->singlePoleModule;

    //wspolczynniki filtru kwadraturowego
    filterFactorCos = module * cos(normalizedFrequency);
    filterFactorSin = module * sin(normalizedFrequency);

    /*rekursywna filtracja kwadraturowa*/
    for (int i = 1; i <sigLength ; i++) {
        _envelope->factorXr[i] = _signal->samplesDifferential[i] + filterFactorCos * _envelope->factorXr[i-1] - filterFactorSin * _envelope->factorXi[i-1];
        _envelope->factorXi[i] = filterFactorCos * _envelope->factorXi[i-1] + filterFactorSin * _envelope->factorXr[i-1];
    }

    /* obwednia - wzor z artykulu*/
    for (int j = 0; j < sigLength ; j++) {
        _envelope->singleFrequencyEnvelope[j] = sqrt(_envelope->factorXr[j]*_envelope->factorXr[j] - _envelope->factorXi[j] * _envelope->factorXi[j]);
    }


    //dystrybuanta
}

