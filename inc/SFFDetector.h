//
// Created by paulina on 07.07.17.
//

#ifndef VOICEACTIVITYDETECTION_SFFDETECTOR_H
#define VOICEACTIVITYDETECTION_SFFDETECTOR_H


#include <aquila/source/WaveFile.h>
#include <aquila/source/WaveFileHandler.h>
#include <vector>

using namespace std;

class SFFDetector {

private:
    struct Signal{
        Signal(string filename);
        virtual ~Signal();
        Aquila::WaveFile* signalOriginal;
        //const Aquila::SignalSource signalOriginal;
        int samplesCount;
        vector<Aquila::SampleType> samplesOriginal;
        vector<Aquila::SampleType> samplesNoised;
        vector<Aquila::SampleType> samplesDifferential;
        Aquila::FrequencyType samplingFrequency;

    };

    struct Envelope{
        Envelope(int samplesCount);
        virtual ~Envelope();
        vector<double> singleFrequencyEnvelope;
        int samplesCount;
        //double* density;
        vector<double> density;
        //double* delt;
        vector<double> delt;
        double singlePoleModule;
        double* filterFactor;
        const double initialThreshold = 0.15;
        //??
        const double detectionSilenceThreshold = 0.12;
        vector<double> factorXr;
        vector<double> factorXi;
        vector<double> factorMi;
        vector<double> factorSigma;
        //co to ? co to ? co to ?
        bool differBef;
        bool smoothing;
        double densityForLeftPart;
        double densityForRightPart;
        double beta;
        const double betaMult = 1.0;
        double theta;
        //??
        const double percent = 0.8;
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
    vector<int> _speachBeginnings;
    //wskaznik do struktury zawierajacej numery indeksow probek
    //kończących aktywnosc mowcy
    vector<int> _speachEndings;
    void addGaussNoise(double noiseMult);
    vector<double> densityForPositiveValues(std::vector<double> VAETab, double max /*, double* VAEDensity,short sPosNb=801*/);
    void singleFrequencyEnvelope(double frequency);
    void singleFrequencyFilteringEnvelope();
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
