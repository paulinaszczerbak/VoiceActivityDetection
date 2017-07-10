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
    struct Envelope{
        double* singleFrequencyEnvelope;
        double* density;
        double* delt;
    };

    struct Signal{
        //tutaj potrzebne 3 tablice - oryginalny sygnal, po filtracji i jakis jeszcze
        //wskazniki na tablice z sygnalem oryginalnym i po przerobkach
        Aquila::WaveFile* signalOriginal;
        int samplesCount;
        Aquila::SampleType* samplesOriginal;
        Aquila::SampleType* samplesNoised;
        Aquila::SampleType* samplesDifferentationed;
        Signal(std::string filename);
        ~Signal();
    };
    //sygnal WAV poddany detekcji
    Signal* signal;
    //Envelope* envelope;

public:
    //SFFDetector(std::string filename):signal(new Signal(filename)){}
    //~SFFDetector(){delete signal;}
    SFFDetector(std::string filename);
    void printSamples();
    void addGaussNoise(double noiseMult);
    void densityForPositiveValues(short sPosNb=801, double max);
};


#endif //VOICEACTIVITYDETECTION_SFFDETECTOR_H
