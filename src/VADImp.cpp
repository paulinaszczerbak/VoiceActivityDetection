/*
 * VADImp.cpp
 *
 *  Created on: 21 lip 2016
 *      Author: paula
 */

//#include "../aquila/include/aquila/source/WaveFile.h"

#include "../inc/VADImp.h"
#include "../inc/EnergyBasedDetector.h"
//#include "../inc/WAVFileSetterImp.h"

VADImp::VADImp() {
    //this->methodNumber=methodNumber;
}

VADImp::~VADImp() {

}

void VADImp::detect(Aquila::WaveFile wav,int methodNumber) {
    //WAVFileSetterImp filename;
    //Aquila::WaveFile wav(file.getFileName());
    if(methodNumber==1){
        //EnergyBasedDetector detector;
        EnergyBasedDetector *detector=new EnergyBasedDetector;
        detector->detect(wav);
        //detector.detect(wav);
    }else if(methodNumber==2){
        //SohnDetector detector;
        //detector.detect();
    }else if(methodNumber==3){
        //jakis trzeci algorytm
        //detector.detect();
    }


}

