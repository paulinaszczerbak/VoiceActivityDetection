//
// Created by paulina on 21.02.17.
//

#include <aquila/source/FramesCollection.h>
#include <iostream>
#include "../inc/SingleFrameEnergyFinder.h"

using namespace std;

SingleFrameEnergyFinder::SingleFrameEnergyFinder() {
    this->singleFrameEnergy=0;
    this->samplesPerFrame=100;
    this->commonSamples=this->samplesPerFrame/2;
}

SingleFrameEnergyFinder::~SingleFrameEnergyFinder() {

}

double SingleFrameEnergyFinder::countSingleFrameEnergy(Aquila::WaveFile wav, size_t frameNumber) {
    Aquila::FramesCollection frames(wav, this->samplesPerFrame,this->commonSamples);
    //obliczam energie w jednej, konkretnej ramce
    double frameEnergy(0);
//    for(size_t i=0; i<frames->getSamplesPerFrame();i++){
//        //iteruje po probkach w ramce
//        frameEnergy=frameEnergy+(frames->frame(frameNumber).sample(i)*frames->frame(frameNumber).sample(i));
//    }
    for(Aquila::SampleType sample : frames.frame(frameNumber)){
        frameEnergy += sample*sample;
    }
    frameEnergy=frameEnergy/frames.getSamplesPerFrame();

    return frameEnergy;
}

unsigned int SingleFrameEnergyFinder::getSamplesPerFrame() {
    return this->samplesPerFrame;
}

unsigned int SingleFrameEnergyFinder::getCommonSamples() {
    return this->commonSamples;
}

void SingleFrameEnergyFinder::setSamplesPerFrame(unsigned int samplesAmount) {
    this->samplesPerFrame=samplesAmount;
    //przy okazji aktualizuje commonSamples
    this->commonSamples=this->samplesPerFrame/2;
}


