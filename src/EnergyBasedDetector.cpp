//
// Created by paulina on 06.02.17.
//
#include <iostream>
#include "../inc/EnergyBasedDetector.h"
#include "../aquila/include/aquila/source/WaveFile.h"
#include "../aquila/include/aquila/source/FramesCollection.h"


EnergyBasedDetector::EnergyBasedDetector(){

}

void EnergyBasedDetector::countSingleFrameEnergy(int frameNumber) {
    Aquila::WaveFile wav("../kabanos.wav");
    int samplesPerFrame(10);
    int commonSamples(5);
    Aquila::FramesCollection frames(wav, samplesPerFrame,commonSamples);
    std::cout<<"liczba ramek:"<<frames.count()<<std::endl;
    std::cout<<"liczba probek w ramce:"<<frames.getSamplesPerFrame()<<std::endl;
    float energy(0);
    //obliczam energie w jednej, konkretnej ramce
    for(int i=0; i<frames.getSamplesPerFrame();i++){
        //iteruje po probkach w ramce
        std::cout<<frames.frame(frameNumber).sample(i)<<std::endl;
        energy=energy+(frames.frame(frameNumber).sample(i)*frames.frame(frameNumber).sample(i));
    }
    energy=energy/frames.getSamplesPerFrame();
    std::cout<<"Energia ramki nr "<<frameNumber<<": "<<energy<<std::endl;


}

float EnergyBasedDetector::getSingleFrameEnergy() {
    return singleFrameEnergy;
}
