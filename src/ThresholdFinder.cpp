//
// Created by paulina on 06.02.17.
//

#include <aquila/source/FramesCollection.h>
#include <iostream>
#include "../inc/ThresholdFinder.h"
#include "../inc/SingleFrameEnergyFinder.h"

#define THRESHOLD 4000

ThresholdFinder::ThresholdFinder() {
    this->threshold=THRESHOLD;
}

ThresholdFinder::~ThresholdFinder() {

}


//void ThresholdFinder::setThreshold(float threshold) {
//    this->threshold=threshold;
//}

double ThresholdFinder::getThreshold() {
    return this->threshold;
}

void ThresholdFinder::InitialThreshold100ms(Aquila::WaveFile wav) {
    SingleFrameEnergyFinder *frame=new SingleFrameEnergyFinder;
    double sumOfEnergy(0);
    //liczba ramek w przeciagu 100ms
    double framesAmount((wav.getSampleFrequency()/10)/frame->getSamplesPerFrame());
    for (size_t i = 0; i <framesAmount ; i++) {
        sumOfEnergy=sumOfEnergy+frame->countSingleFrameEnergy(wav,i);
        std::cout<<"suma"<<sumOfEnergy<<std::endl;
    }
    this->threshold=sumOfEnergy/framesAmount;
}
