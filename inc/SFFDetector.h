//
// Created by paulina on 07.07.17.
//

#ifndef VOICEACTIVITYDETECTION_SFFDETECTOR_H
#define VOICEACTIVITYDETECTION_SFFDETECTOR_H


#include <aquila/source/WaveFile.h>
#include <aquila/source/WaveFileHandler.h>

class SFFDetector {

private:
//    Aquila::WaveFile* _signalOriginal;
//    int _samplesCount;
//    Aquila::SampleType*_samplesOriginal; //original
//    Aquila::SampleType* _samplesAfterFiltering; //
//    Aquila::SampleType* _samplesSpectrum;

    struct Signal{
        //tutaj potrzebne 3 tablice - oryginalny sygnal, po filtracji i jakis jeszcze
        //wskazniki na tablice z sygnalem oryginalnym i po przerobkach
        Aquila::WaveFile* signalOriginal;
        int samplesCount;
        int frameLength;
        Aquila::SampleType* samplesOriginal;
        Aquila::SampleType* samplesNoised;
        Aquila::SampleType* samplesDifferential;
        Aquila::FrequencyType samplingFrequency;
        Signal(std::string filename);
        virtual ~Signal();
    };

    struct Envelope{
        double* singleFrequencyEnvelope;
        int samplesCount;
        double* density;
        double* delt;
        double singlePoleModule;
        double* filterFactor;
        double firstThreshold;
        double* factorXr;
        double* factorXi;
        double* factorMi;
        double* factorSigma;
        //co to ? co to ? co to ?
        bool differBef;
        Envelope(int samplesCount);
        virtual ~Envelope();
    };
    //sygnal WAV poddany detekcji
    Signal* _signal;
    //obwiednia sygnału
    Envelope* _envelope;
    double maxValue();
    const double PI = 3.14;
public:
    //SFFDetector(std::string filename):signal(new Signal(filename)){}
    //~SFFDetector(){delete signal;}
    SFFDetector(std::string filename);
    void printSamples();
    void addGaussNoise(double noiseMult);
    void densityForPositiveValues(double* VAETab, double max, double* VAEDensity,short sPosNb=801);
    void singleFrequencyEnvelope(double frequency);
};


#endif //VOICEACTIVITYDETECTION_SFFDETECTOR_H
