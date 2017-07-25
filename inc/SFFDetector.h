//
// Created by paulina on 07.07.17.
//

#ifndef VOICEACTIVITYDETECTION_SFFDETECTOR_H
#define VOICEACTIVITYDETECTION_SFFDETECTOR_H


#include <aquila/source/WaveFile.h>
#include <aquila/source/WaveFileHandler.h>

class SFFDetector {

private:
    struct Signal{
        Signal(std::string filename);
        virtual ~Signal();
        //tutaj potrzebne 3 tablice - oryginalny sygnal, po filtracji i jakis jeszcze
        //wskazniki na tablice z sygnalem oryginalnym i po przerobkach
        Aquila::WaveFile* signalOriginal;
        int samplesCount;
        int frameLength;
        Aquila::SampleType* samplesOriginal;
        Aquila::SampleType* samplesNoised;
        Aquila::SampleType* samplesDifferential;
        Aquila::FrequencyType samplingFrequency;

    };

    struct Envelope{
        Envelope(int samplesCount);
        virtual ~Envelope();
        double* singleFrequencyEnvelope;
        int samplesCount;
        double* density;
        double* delt;
        double singlePoleModule;
        double* filterFactor;
        const double initialThreshold = 0.15;
        //??
        const double detectionSilenceThreshold = 0.12;
        double* factorXr;
        double* factorXi;
        double* factorMi;
        double* factorSigma;
        //co to ? co to ? co to ?
        bool differBef;
        bool smoothing;
        //???
        double densityForLeftPart;
        double densityForRightPart;

    };
    //sygnal WAV poddany detekcji
    Signal* _signal;
    //obwiednia sygnału
    Envelope* _envelope;
    const double PI = 3.14;
    //co to ?????
    static const int sPosNb = 801;
    //wskaznik do struktury zawierajacej numery indeksow probek
    //rozpoczynajacych aktywnosc mowcy
    double* _speachBeginnings;
    //wskaznik do struktury zawierajacej numery indeksow probek
    //kończących aktywnosc mowcy
    double* _speachEndings;
    void addGaussNoise(double noiseMult);
    void densityForPositiveValues(double* VAETab, double max /*, double* VAEDensity,short sPosNb=801*/);
    void singleFrequencyEnvelope(double frequency);
    void singleFrequencyFilteringEnvelope();
    double findMaxValue(double* array);
    double findMaxAbsValue(double* array);
    double singleFrequencyFilteringBeta();

public:
    //SFFDetector(std::string filename):signal(new Signal(filename)){}
    //~SFFDetector(){delete signal;}
    SFFDetector(std::string filename);
    void printSamples();
    void detect();
};


#endif //VOICEACTIVITYDETECTION_SFFDETECTOR_H
