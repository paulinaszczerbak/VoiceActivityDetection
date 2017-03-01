//
// Created by paulina on 06.02.17.
//

#include <aquila/source/FramesCollection.h>
#include <iostream>
#include "../inc/ThresholdFinder.h"
#include "../inc/SingleFrameEnergyFinder.h"

#define THRESHOLD 10

ThresholdFinder::ThresholdFinder() {
    this->threshold=THRESHOLD;
    this->Emax=1;
    this->Emin=1;
    this->scalingFactor=0;
    this->initialValue=0;
}

ThresholdFinder::~ThresholdFinder() {

}


double ThresholdFinder::getThreshold() {
    return this->threshold;
}

//oblicza poczatkowy prog detekcji na podstawie sredniej energii z pierwszych 100ms nagrania
//stwierdzono, ze przed kazda wypowiedzia czlowiek potrzebuje chwili na nabranie powietrza itp
void ThresholdFinder::calculateThreshold100ms(Aquila::WaveFile wav) {
    SingleFrameEnergyFinder *frame=new SingleFrameEnergyFinder;
    double sumOfEnergy(0);
    //liczba ramek w przeciagu 100ms
    double framesAmount((wav.getSampleFrequency()/10)/frame->getSamplesPerFrame());
    for (size_t i = 0; i <framesAmount ; i++) {
        sumOfEnergy=sumOfEnergy+frame->countSingleFrameEnergy(wav,i);
    }
    this->threshold=(sumOfEnergy/framesAmount);
}

void ThresholdFinder::calculateThresholdMinMax(Aquila::WaveFile wav, size_t currentFrameNumber) {

    double singleFrameEnergy=this->frameEn.countSingleFrameEnergy(wav,currentFrameNumber);

    //jezeli to pierwsza ramka
    if(currentFrameNumber==0) {
        this->initialValue=singleFrameEnergy;
        this->Emax=initialValue;
        this->Emin=initialValue;
    }

    //jezeli energia tej ramki jest wieksza niz Emax
    if(singleFrameEnergy>Emax){
        Emax=singleFrameEnergy;
    }
        //jezeli energia tej ramki jest mniejsza niz Emin
    else if(singleFrameEnergy<Emin) {
        if(singleFrameEnergy==0){
            this->Emin=this->initialValue;
            //resetDelta
        }
        else{
            Emin=singleFrameEnergy;
            //resetDelta
        }
    }else{
        //resetDelta
        std::cout<<"dupa"<<std::endl;
    }


    this->scalingFactor=(Emax-Emin)/Emax;
    this->threshold=((1-scalingFactor)*Emax)+(scalingFactor*Emin);

}
