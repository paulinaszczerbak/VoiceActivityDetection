//
// Created by paulina on 06.02.17.
//
#include <iostream>
#include <fstream>
#include "../inc/EnergyBasedDetector.h"

//#include "../aquila/include/aquila/source/WaveFile.h"
#include "../aquila/include/aquila/source/FramesCollection.h"


EnergyBasedDetector::EnergyBasedDetector(){
    //this->singleFrameEnergy=0;
    this->singleFrameEnergy=0;
    this->samplesPerFrame=12;
    this->commonSamples=this->samplesPerFrame/2;
}


EnergyBasedDetector::~EnergyBasedDetector() {

}


double EnergyBasedDetector::countSingleFrameEnergy(Aquila::WaveFile wav,size_t frameNumber) {

    Aquila::FramesCollection frames(wav, this->samplesPerFrame,this->commonSamples);
    //obliczam energie w jednej, konkretnej ramce
    for(size_t i=0; i<frames.getSamplesPerFrame();i++){
        //iteruje po probkach w ramce
        this->singleFrameEnergy=this->singleFrameEnergy+(frames.frame(frameNumber).sample(i)*frames.frame(frameNumber).sample(i));
    }
    this->singleFrameEnergy=this->singleFrameEnergy/frames.getSamplesPerFrame();
    //std::cout<<"Energia ramki nr "<<frameNumber<<": "<<this->singleFrameEnergy<<std::endl;

    return this->singleFrameEnergy;
}
//
//double EnergyBasedDetector::getSingleFrameEnergy() {
//    return this->singleFrameEnergy;
//}

void EnergyBasedDetector::detect(Aquila::WaveFile wav) {
    //próg detekcji
    ThresholdFinder threshold;
    //ustawiam liczbe ramek w pliku
    setFramesAmount(wav);
    //system("rm resultToPlot");
    system("touch resultToPlot");
    //otwieram plik do zapisu
    std::ofstream file("resultToPlot");
    int xValue(0);
    if(file){
        for (size_t i = 0; i <this->framesAmount ; i++) {
            if(this->countSingleFrameEnergy(wav,i)<threshold.getThreshold()) {
                //file<<0<<std::endl<<0<<std::endl<<0<<std::endl<<0<<std::endl<<0<<std::endl;
                file<<xValue<<" "<<0<<std::endl;
                xValue+=this->samplesPerFrame/2;//5;
            }
            else {
                //file << 10000 << std::endl << 10000 << std::endl << 10000 << std::endl << 10000 << std::endl << 10000<< std::endl;
                file<<xValue<<" "<<10000<<std::endl;
                xValue+=this->samplesPerFrame/2;//5;
            }
        }
        file.close();
    } else{
        std::cout<<"BLAD: nie mozna otworzyc pliku"<<std::endl;
    }


}

void EnergyBasedDetector::setFramesAmount(Aquila::WaveFile wav) {
    //Aquila::WaveFile wav(WAVFileSetterImp::getFilename());
    Aquila::FramesCollection frames(wav, this->samplesPerFrame,this->commonSamples);
    this->framesAmount=frames.count();

}
//
//int EnergyBasedDetector::getFramesAmount() {
//    return this->framesAmount;
//}
