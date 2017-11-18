//
// Created by paulina on 16.09.17.
//

#include "../inc/Signal.h"

Signal::Signal(string filename) {
    signalOriginal = new Aquila::WaveFile(filename);
    //samplesCount = signalOriginal->getSamplesCount();
    samplesCount = signalOriginal->getSamplesCount();
    samplingFrequency = signalOriginal->getSampleFrequency();

    samplesOriginal.reserve(samplesCount);
    samplesOriginal.assign(signalOriginal->begin(),signalOriginal->end());

    samplesNoised.reserve(samplesCount);
    samplesDifferential.reserve(samplesCount);

//    fill(samplesNoised.begin(), samplesNoised.end(), 0);
//    fill(samplesDifferential.begin(), samplesDifferential.end(), 0);
}

Signal::~Signal() {
    delete signalOriginal;
}