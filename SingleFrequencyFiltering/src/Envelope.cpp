//
// Created by paulina on 16.09.17.
//

#include "../inc/Envelope.h"

Envelope::Envelope(int samplesCount) {
    this->samplesCount=samplesCount;
    this->differBef = true;
    this->smoothing = true;

    singleFrequencyEnvelope.reserve(samplesCount);
    factorXr.reserve(samplesCount);
    factorXi.reserve(samplesCount);
    factorMi.reserve(samplesCount);
    factorSigma.reserve(samplesCount);
    delt.reserve(samplesCount);

    fill(singleFrequencyEnvelope.begin(), singleFrequencyEnvelope.end(),0);
    fill(factorXr.begin(), factorXr.end(),0);
    fill(factorXi.begin(), factorXi.end(),0);
    fill(factorMi.begin(), factorMi.end(),0);
    fill(factorSigma.begin(), factorSigma.end(),0);
    fill(delt.begin(), delt.end(), 0);

}

Envelope::~Envelope() {
}

