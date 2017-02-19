//
// Created by paulina on 06.02.17.
//
#include <iostream>
#include <fstream>
#include "../inc/EnergyBasedDetector.h"

#include "../aquila/include/aquila/source/WaveFile.h"
#include "../aquila/include/aquila/source/FramesCollection.h"

#include "../inc/WAVFileSetterImp.h"

EnergyBasedDetector::EnergyBasedDetector(){
    //this->singleFrameEnergy=0;
    this->singleFrameEnergy=0;
    this->samplesPerFrame=10;
    this->commonSamples=5;
}


EnergyBasedDetector::~EnergyBasedDetector() {

}


float EnergyBasedDetector::countSingleFrameEnergy(int frameNumber) {
    //pobieram nazwe pliku wav
    Aquila::WaveFile wav(WAVFileSetterImp::getFileName());

    //std::cout<<"nazwa pliku: "<<WAVFileSetterImp::getFileName()<<std::endl;
    Aquila::FramesCollection frames(wav, this->samplesPerFrame,this->commonSamples);
    //std::cout<<"liczba ramek:"<<frames.count()<<std::endl;
    //std::cout<<"liczba probek w ramce:"<<frames.getSamplesPerFrame()<<std::endl;
    //obliczam energie w jednej, konkretnej ramce
    for(int i=0; i<frames.getSamplesPerFrame();i++){
        //iteruje po probkach w ramce
        this->singleFrameEnergy=this->singleFrameEnergy+(frames.frame(frameNumber).sample(i)*frames.frame(frameNumber).sample(i));
    }
    this->singleFrameEnergy=this->singleFrameEnergy/frames.getSamplesPerFrame();
    //std::cout<<"Energia ramki nr "<<frameNumber<<": "<<this->singleFrameEnergy<<std::endl;

    return this->singleFrameEnergy;
}

float EnergyBasedDetector::getSingleFrameEnergy() {
    return 0;//singleFrameEnergy;
}

void EnergyBasedDetector::detect() {
    //próg detekcji
    ThresholdFinder threshold;
    //ustawiam liczbe ramek w pliku
    setFramesAmount();
    //system("rm resultToPlot");
    system("touch resultToPlot");
    //otwieram plik do zapisu
    std::ofstream file("resultToPlot");
    int xValue(0);
    if(file){
        for (int i = 0; i <this->framesAmount ; i++) {
            if(this->countSingleFrameEnergy(i)<threshold.getThreshold()) {
                //file<<0<<std::endl<<0<<std::endl<<0<<std::endl<<0<<std::endl<<0<<std::endl;
                file<<xValue<<" "<<0<<std::endl;
                xValue+=5;
            }
            else {
                //file << 10000 << std::endl << 10000 << std::endl << 10000 << std::endl << 10000 << std::endl << 10000<< std::endl;
                file<<xValue<<" "<<10000<<std::endl;
                xValue+=5;
            }
        }
        file.close();
    } else{
        std::cout<<"BLAD: nie mozna otworzyc pliku"<<std::endl;
    }


}

void EnergyBasedDetector::setFramesAmount() {
    Aquila::WaveFile wav(WAVFileSetterImp::getFileName());
    Aquila::FramesCollection frames(wav, this->samplesPerFrame,this->commonSamples);
    this->framesAmount=frames.count();

}

int EnergyBasedDetector::getFramesAmount() {
    return this->framesAmount;
}
