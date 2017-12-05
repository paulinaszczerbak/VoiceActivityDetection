//
// Created by paulina on 07.07.17.
//

#ifndef VOICEACTIVITYDETECTION_SFFDETECTOR_H
#define VOICEACTIVITYDETECTION_SFFDETECTOR_H


#include <aquila/source/WaveFile.h>
#include <aquila/source/WaveFileHandler.h>
#include <vector>
#include <aquila/source/FramesCollection.h>
#include "../SingleFrequencyFilteringMc/inc/Envelope.h"
#include "../SingleFrequencyFilteringMc/inc/Signal.h"

using namespace std;

class SFFDetector {

private:
    //sygnal WAV poddany detekcji
    Signal* _signal;

    Aquila::SampleType* signalOriginal;

    //obwiednia sygnału
    Envelope* _envelope;
    const double PI = 3.14;
    //co to ?????
    static const int sPosNb = 801;
    //wskaznik do struktury zawierajacej numery indeksow probek
    //rozpoczynajacych aktywnosc mowcy
    vector<int> _speachBeginnings;
    //wskaznik do struktury zawierajacej numery indeksow probek
    //kończących aktywnosc mowcy
    vector<int> _speachEndings;
    vector<double> addGaussNoise(double noiseMult);
    vector<double> densityForPositiveValues(std::vector<double> VAETab, double max /*, double* VAEDensity,short sPosNb=801*/);
    vector<double> singleFrequencyEnvelope(double frequency);
    vector<double> singleFrequencyFilteringEnvelope();
    double findMaxValue(double* array);
    double findMaxAbsValue(double* array);
    double countBeta();
    double countTheta();
    double calculateRo(Signal* signal);
    vector<double> smooth(std::vector<double> signal);
    double countEnergy(Aquila::FramesCollection* frames, Aquila::SampleType frameIndex);
    void singleFrequencyFilteringDetect();

public:
    //SFFDetector(std::string filename):signal(new Signal(filename)){}
    SFFDetector(std::string filename);
    ~SFFDetector(){delete _signal, _envelope;}
    void printSamples();
    void detect();
};


#endif //VOICEACTIVITYDETECTION_SFFDETECTOR_H
