//
// Created by paulina on 06.02.17.
//

#include <aquila/source/FramesCollection.h>
#include "../inc/ThresholdFinder.h"
#include "../inc/SingleFrameEnergyFinder.h"

#define THRESHOLD 10

ThresholdFinder::ThresholdFinder() {
    this->threshold=THRESHOLD;
}

ThresholdFinder::~ThresholdFinder() {

}


double ThresholdFinder::getThreshold() {
    return this->threshold;
}

//oblicza poczatkowy prog detekcji na podstawie sredniej energii z pierwszych 100ms nagrania
//stwierdzono, ze przed kazda wypowiedzia czlowiek potrzebuje chwili na nabranie powietrza itp
void ThresholdFinder::initialThreshold100ms(Aquila::WaveFile wav) {
    SingleFrameEnergyFinder *frame=new SingleFrameEnergyFinder;
    double sumOfEnergy(0);
    //liczba ramek w przeciagu 100ms
    double framesAmount((wav.getSampleFrequency()/10)/frame->getSamplesPerFrame());
    for (size_t i = 0; i <framesAmount ; i++) {
        sumOfEnergy=sumOfEnergy+frame->countSingleFrameEnergy(wav,i);
    }
    this->threshold=(sumOfEnergy/framesAmount);
}
