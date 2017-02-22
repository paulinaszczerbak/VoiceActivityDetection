//
// Created by paulina on 06.02.17.
//
#include <iostream>
#include <fstream>
#include "../inc/EnergyBasedDetector.h"

//#include "../aquila/include/aquila/source/WaveFile.h"
#include "../aquila/include/aquila/source/FramesCollection.h"


EnergyBasedDetector::EnergyBasedDetector(){

}


EnergyBasedDetector::~EnergyBasedDetector() {

}

void EnergyBasedDetector::detect(Aquila::WaveFile wav) {
    //próg detekcji
    initialThreshold100ms(wav);
    std::cout<<"próg detekcji "<<getThreshold()<<std::endl;
    Aquila::FramesCollection *frames=new Aquila::FramesCollection(wav, getSamplesPerFrame(), getCommonSamples());
    size_t framesAmount=frames->count();
    system("touch resultToPlot");
    //otwieram plik do zapisu
    std::ofstream file("resultToPlot");
    int xValue(0);
    if(file){
        for (size_t i = 0; i <framesAmount ; i++) {
            if(countSingleFrameEnergy(wav,i)<=getThreshold()){
                file<<xValue<<" "<<0<<std::endl;
                xValue+=getSamplesPerFrame()/2;//5;
            }
            else {
                file<<xValue<<" "<<10000<<std::endl;
                xValue+=getSamplesPerFrame()/2;//5;
            }
        }
        file.close();
    } else{
        std::cout<<"BLAD: nie mozna otworzyc pliku"<<std::endl;
    }


}

