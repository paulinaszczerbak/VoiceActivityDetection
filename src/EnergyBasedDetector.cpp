//
// Created by paulina on 06.02.17.
//
#include <iostream>
#include <fstream>
#include "../inc/EnergyBasedDetector.h"

//#include "../aquila/include/aquila/source/WaveFile.h"
#include "../aquila/include/aquila/source/FramesCollection.h"

using namespace std;

EnergyBasedDetector::EnergyBasedDetector(){
    this->threshold=new ThresholdFinder();
}


EnergyBasedDetector::~EnergyBasedDetector() {
}

void EnergyBasedDetector::detect(Aquila::WaveFile wav) {
//    //dlugosc ramki na 20ms - zdefiniowane w VADImp
//    //ustawiam liczbe probek w ramce
    unsigned int samplesInSingleFrameAmount(wav.getSampleFrequency()*getFrameLengthInSECs());
    setSamplesPerFrame(samplesInSingleFrameAmount);
    Aquila::SignalSource wavNoised = addGaussianNoiseToSignal(wav);
    //próg detekcji obliczany na podstawie pierwszych 100ms pliku
    threshold->calculateThreshold100ms(wavNoised);

    //std::cout<<"próg detekcji "<<getThreshold()<<std::endl;

    Aquila::FramesCollection *frames=new Aquila::FramesCollection(wavNoised, getSamplesPerFrame(), getCommonSamples());
    //std::cout<<"samples "<<getSamplesPerFrame()<<std::endl;
    size_t framesAmount=frames->count();

    //zapis do pliku 0000111000 - wynik detekcji
    //todo: zmienić na plik zawierajacy punkty, w ktorych jest ZMIANA
    //writing to file to plot results
    system("touch signalToPlotEnergy");
    //otwieram plik do zapisu
    ofstream file1("signalToPlotEnergy");
    if(file1){
        for (size_t i = 0; i< wavNoised.getSamplesCount() ; i++) {
            file1 << wavNoised.sample(i) << endl;
        }
        file1.close();
    } else{
        cout<<"BLAD: nie mozna otworzyc pliku"<<endl;
    }


    system("touch resultToPlotEnergy");
    //otwieram plik do zapisu
    std::ofstream file("resultToPlotEnergy");
    int xValue(0);
    if(file){
        file<<xValue<<" "<<0<<endl;
        xValue+=getCommonSamples();
        for (size_t i = 1; i <framesAmount-1 ; i++) {
            //estymowany prog detekcji
            threshold->calculateThresholdEminEmax(wav,i);
            std::cout<<"próg detekcji "<<threshold->getThreshold()<<std::endl;
            //std::cout<<"wychodzi"<<std::endl;
            double frameEnergy = countSingleFrameEnergy(wav,i);
            cout<<"frame en: "<<frameEnergy<<endl;
            cout<<"threshold: "<<threshold->getThreshold()<<endl;

            if(frameEnergy<=threshold->getThreshold()){
                file<<xValue<<" "<<0<<std::endl;
                xValue+=getCommonSamples();
                //xValue+=(getSamplesPerFrame()/2);
            }
            else {
                file<<xValue<<" "<<1<<std::endl;
                xValue+=getCommonSamples();
                //xValue+=(getSamplesPerFrame()/2);
            }
        }
        file<<xValue<<" "<<0<<endl;
        file.close();
    } else{
        std::cout<<"BLAD: nie mozna otworzyc pliku"<<std::endl;
    }

    //************************TUTAJ BEZ RAMEK - NA PROBKACH
    //próg detekcji obliczany na podstawie pierwszych 100ms pliku
//    unsigned int samplesInSingleFrameAmount(wav.getSampleFrequency()*getFrameLengthInSECs());
//    setSamplesPerFrame(samplesInSingleFrameAmount);
//    calculateThreshold100ms(wav);
//
//    //std::cout<<"próg detekcji "<<getThreshold()<<std::endl;
//    system("touch resultToPlot");
//    //otwieram plik do zapisu
//    std::ofstream file("resultToPlot");
//    int xValue(0);
//    if(file){
//        for (size_t i = 0; i <wav.getSampleFrequency()*wav.getAudioLength()/1000 ; i++) {
//            //estymowany prog detekcji
//            //std::cout<<"wchodzi do estymowania progu"<<std::endl;
//            //calculateThresholdEminEmax(wav,i);
//            std::cout<<"próg detekcji "<<getThreshold()<<std::endl;
//            //std::cout<<"wychodzi"<<std::endl;
//            if((wav.sample(i)*wav.sample(i))<=getThreshold()){
//                file<<0<<std::endl;
//                //xValue+=(getSamplesPerFrame()/2);
//            }
//            else {
//                file<<10000<<std::endl;
//
//                //xValue+=(getSamplesPerFrame()/2);
//            }
//        }
//        file.close();
//    } else{
//        std::cout<<"BLAD: nie mozna otworzyc pliku"<<std::endl;
//    }


}

Aquila::SignalSource EnergyBasedDetector::addGaussianNoiseToSignal(Aquila::WaveFile signal) {
    vector<Aquila::SampleType> noised(signal.begin(), signal.end());
    // Define random generator with Gaussian distribution
    const double mean = 0.0;
    const double stddev = 0.1;

    auto dist = std::bind(std::normal_distribution<double>{mean, stddev},
                          std::mt19937(std::random_device{}()));

    // Add Gaussian noise
    for (auto& x : noised) {
        x = x + dist();
    }

    return Aquila::SignalSource(noised, signal.getSampleFrequency());
}

