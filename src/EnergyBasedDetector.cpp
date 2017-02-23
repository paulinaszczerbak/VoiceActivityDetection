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
    //dlugosc ramki na 20ms - zdefiniowane w VADImp
    //ustawiam liczbe probek w ramce
    unsigned int samplesInSingleFrameAmount(wav.getSampleFrequency()*getFrameLengthInSECs());
    setSamplesPerFrame(samplesInSingleFrameAmount);

    //próg detekcji obliczany na podstawie pierwszych 100ms pliku
    initialThreshold100ms(wav);

    std::cout<<"próg detekcji "<<getThreshold()<<std::endl;

    Aquila::FramesCollection *frames=new Aquila::FramesCollection(wav, getSamplesPerFrame(), getCommonSamples());
    std::cout<<"samples "<<getSamplesPerFrame()<<std::endl;
    size_t framesAmount=frames->count();

    system("touch resultToPlot");
    //otwieram plik do zapisu
    std::ofstream file("resultToPlot");
    int xValue(0);
    if(file){
        for (size_t i = 0; i <framesAmount ; i++) {
            if(countSingleFrameEnergy(wav,i)<=getThreshold()){
                file<<xValue<<" "<<0<<std::endl;
                xValue+=(getSamplesPerFrame()/2);
            }
            else {
                file<<xValue<<" "<<10000<<std::endl;
                xValue+=(getSamplesPerFrame()/2);
            }
        }
        file.close();
    } else{
        std::cout<<"BLAD: nie mozna otworzyc pliku"<<std::endl;
    }


}

