//
// Created by paulina on 21.02.17.
//

#include <aquila/source/FramesCollection.h>
#include "../inc/SingleFrameEnergyFinder.h"

SingleFrameEnergyFinder::SingleFrameEnergyFinder() {
    this->singleFrameEnergy=0;
    this->samplesPerFrame=10;
    this->commonSamples=this->samplesPerFrame/2;
}

SingleFrameEnergyFinder::~SingleFrameEnergyFinder() {

}

double SingleFrameEnergyFinder::countSingleFrameEnergy(Aquila::WaveFile wav, size_t frameNumber) {
    Aquila::FramesCollection *frames=new Aquila::FramesCollection(wav, this->samplesPerFrame,this->commonSamples);
    //obliczam energie w jednej, konkretnej ramce
    for(size_t i=0; i<frames->getSamplesPerFrame();i++){
        //iteruje po probkach w ramce
        this->singleFrameEnergy=this->singleFrameEnergy+(frames->frame(frameNumber).sample(i)*frames->frame(frameNumber).sample(i));
    }
    this->singleFrameEnergy=this->singleFrameEnergy/frames->getSamplesPerFrame();
    //std::cout<<"Energia ramki nr "<<frameNumber<<": "<<this->singleFrameEnergy<<std::endl;

    return this->singleFrameEnergy;
}

unsigned int SingleFrameEnergyFinder::getSamplesPerFrame() {
    return this->samplesPerFrame;
}

unsigned int SingleFrameEnergyFinder::getCommonSamples() {
    return this->commonSamples;
}

