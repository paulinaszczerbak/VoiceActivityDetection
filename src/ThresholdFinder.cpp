//
// Created by paulina on 06.02.17.
//

#include <aquila/source/FramesCollection.h>
#include <iostream>
#include "../inc/ThresholdFinder.h"
#include "../inc/SingleFrameEnergyFinder.h"

#define THRESHOLD 10
#define DELTA 1.00
#define LAMBDA 0.990


ThresholdFinder::ThresholdFinder() {
    threshold=THRESHOLD;
    Emax=1;
    Emin=1;
    scalingFactor=0;
    initialValue=0;
    delta=DELTA;
}

ThresholdFinder::~ThresholdFinder() {

}

double ThresholdFinder::getThreshold() {
    return threshold;
}

//oblicza poczatkowy prog detekcji na podstawie sredniej energii z pierwszych 100ms nagrania
//stwierdzono, ze przed kazda wypowiedzia czlowiek potrzebuje chwili na nabranie powietrza itp
void ThresholdFinder::calculateThreshold100ms(Aquila::SignalSource wav) {
    //*********************RAMKI
    SingleFrameEnergyFinder *frame=new SingleFrameEnergyFinder;
    double sumOfEnergy(0);
    //liczba ramek w przeciagu 100ms
    double framesAmount((wav.getSampleFrequency()*0.1)/frame->getSamplesPerFrame());
    for (size_t i = 0; i <framesAmount ; i++) {
        sumOfEnergy=sumOfEnergy+frame->countSingleFrameEnergy(wav,i);
    }
    threshold=(sumOfEnergy/framesAmount);

//    //*******NA PODSTAWIE PROBEK - srednia energia z poczatkowych 100ms
//    double sumOfEnergy(0);
//    for (size_t i = 0; i <wav.getSampleFrequency()*0.1 ; i++) {
//        sumOfEnergy=sumOfEnergy+(wav.sample(i)*wav.sample(i));
//    }
//    threshold=(sumOfEnergy/wav.getSampleFrequency()*0.1);
}

void ThresholdFinder::calculateThresholdEminEmax(Aquila::WaveFile wav, size_t currentFrameNumber) {

    double singleFrameEnergy=frameEn.countSingleFrameEnergy(wav,currentFrameNumber);

    //jezeli to pierwsza ramka
    if(currentFrameNumber==0) {
        initialValue=singleFrameEnergy;
        if(initialValue==0){
            initialValue=1;
            Emax = initialValue;
            Emin = initialValue;
        }else {
            Emax = initialValue;
            Emin = initialValue;
        }
    }

    //Emin nieznacznie wzrasta dla każdej ramki
    if(currentFrameNumber>0){
        delta=delta*1.0001;
        Emin=Emin*delta;
    }
    //jezeli energia tej ramki jest wieksza niz Emax
    if(singleFrameEnergy>Emax){
        Emax=singleFrameEnergy;
    }
        //jezeli energia tej ramki jest mniejsza niz Emin
    else if(singleFrameEnergy<Emin) {
        if(singleFrameEnergy==0){
            Emin=initialValue;
            //resetDelta
            delta=DELTA;
        }
        else{
            Emin=singleFrameEnergy;
            //resetDelta
            delta=DELTA;
        }
    }else{
        //resetDelta
        delta=DELTA;
    }


    scalingFactor=(Emax-Emin)/Emax;
//    scalingFactor = LAMBDA;
//    std::cout<<Emin<<" "<<Emax<<std::endl;
//    std::cout<<scalingFactor<<std::endl;
    threshold=((1-scalingFactor)*Emax)+(scalingFactor*Emin);
    threshold*=1000;

}
