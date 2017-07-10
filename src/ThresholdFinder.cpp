//
// Created by paulina on 06.02.17.
//

#include <aquila/source/FramesCollection.h>
#include <iostream>
#include "../inc/ThresholdFinder.h"
#include "../inc/SingleFrameEnergyFinder.h"

#define THRESHOLD 10
#define DELTA 1.00

ThresholdFinder::ThresholdFinder() {
    this->threshold=THRESHOLD;
    this->Emax=1;
    this->Emin=1;
    this->scalingFactor=0;
    this->initialValue=0;
    this->delta=DELTA;
}

ThresholdFinder::~ThresholdFinder() {

}


double ThresholdFinder::getThreshold() {
    return this->threshold;
}

//oblicza poczatkowy prog detekcji na podstawie sredniej energii z pierwszych 100ms nagrania
//stwierdzono, ze przed kazda wypowiedzia czlowiek potrzebuje chwili na nabranie powietrza itp
void ThresholdFinder::calculateThreshold100ms(Aquila::WaveFile wav) {
    //*********************RAMKI
    SingleFrameEnergyFinder *frame=new SingleFrameEnergyFinder;
    double sumOfEnergy(0);
    //liczba ramek w przeciagu 100ms
    double framesAmount((wav.getSampleFrequency()/10)/frame->getSamplesPerFrame());
    for (size_t i = 0; i <framesAmount ; i++) {
        sumOfEnergy=sumOfEnergy+frame->countSingleFrameEnergy(wav,i);
    }
    this->threshold=(sumOfEnergy/framesAmount);

//    //*******NA PODSTAWIE PROBEK - srednia energia z poczatkowych 100ms
//    double sumOfEnergy(0);
//    for (size_t i = 0; i <wav.getSampleFrequency()*0.1 ; i++) {
//        sumOfEnergy=sumOfEnergy+(wav.sample(i)*wav.sample(i));
//    }
//    this->threshold=(sumOfEnergy/wav.getSampleFrequency()*0.1);
}

void ThresholdFinder::calculateThresholdEminEmax(Aquila::WaveFile wav, size_t currentFrameNumber) {

    double singleFrameEnergy=this->frameEn.countSingleFrameEnergy(wav,currentFrameNumber);

    //jezeli to pierwsza ramka
    if(currentFrameNumber==0) {
        this->initialValue=singleFrameEnergy;
        if(initialValue==0){
            this->initialValue=1;
            this->Emax = this->initialValue;
            this->Emin = this->initialValue;
        }else {
            this->Emax = this->initialValue;
            this->Emin = this->initialValue;
        }
    }

    //Emin nieznacznie wzrasta dla każdej ramki
    if(currentFrameNumber>0){
        this->delta=this->delta*1.0001;
        this->Emin=this->Emin*this->delta;
    }
    //jezeli energia tej ramki jest wieksza niz Emax
    if(singleFrameEnergy>this->Emax){
        this->Emax=singleFrameEnergy;
    }
        //jezeli energia tej ramki jest mniejsza niz Emin
    else if(singleFrameEnergy<this->Emin) {
        if(singleFrameEnergy==0){
            this->Emin=this->initialValue;
            //resetDelta
            this->delta=DELTA;
        }
        else{
            this->Emin=singleFrameEnergy;
            //resetDelta
            this->delta=DELTA;
        }
    }else{
        //resetDelta
        this->delta=DELTA;
    }


    this->scalingFactor=(Emax-Emin)/Emax;
    //std::cout<<Emin<<" "<<Emax<<std::endl;
    //std::cout<<scalingFactor<<std::endl;
    this->threshold=((1-this->scalingFactor)*this->Emax)+(this->scalingFactor*this->Emin);

}
