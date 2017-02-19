//
// Created by paulina on 15.02.17.
//
#include <iostream>
#include <fstream>

#include "../inc/WAVFileSetterImp.h"
#include "../inc/WAVFileSetter.h"

#include "../aquila/include/aquila/source/WaveFile.h"

WAVFileSetterImp::WAVFileSetterImp() {
    this->fileName="../kabanos.wav";

}

WAVFileSetterImp::~WAVFileSetterImp() {

}

void WAVFileSetterImp::setFileName(std::string fileName) {
    this->fileName=fileName;
}

std::string WAVFileSetterImp::getFileName() {
    return this->fileName;
}




