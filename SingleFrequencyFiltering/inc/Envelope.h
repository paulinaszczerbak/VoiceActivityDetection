//
// Created by paulina on 16.09.17.
//

#ifndef VOICEACTIVITYDETECTION_ENVELOPE_H
#define VOICEACTIVITYDETECTION_ENVELOPE_H

#include <vector>

using namespace std;

class Envelope {
    virtual ~Envelope();
    vector<double> singleFrequencyEnvelope;
    int samplesCount;
    double* filterFactor;
    double densityForLeftPart;
    double densityForRightPart;
public:
    Envelope(int samplesCount);

    const double singlePoleModule = 0.97;
    vector<double> factorXr;
    vector<double> factorXi;
    //double* density;
    vector<double> density;
    const double initialThreshold = 0.15;
    //co to ? co to ? co to ?
    bool differBef;
    //double* delt;
    vector<double> delt;
    bool smoothing;
    double beta;
    const double betaMult = 1.0;
    double theta;
    vector<double> factorMi;
    vector<double> factorSigma;
//??
const double detectionSilenceThreshold = 0.12;
//??
const double percent = 0.8;
};


#endif //VOICEACTIVITYDETECTION_ENVELOPE_H
