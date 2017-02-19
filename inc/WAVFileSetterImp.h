//
// Created by paulina on 15.02.17.
//Implementacja klasy WAVFileSetter do ustawiania nazwy pliku
//
#include <iostream>

#ifndef VOICEACTIVITYDETECTION_WAVFILESETTERIMP_H
#define VOICEACTIVITYDETECTION_WAVFILESETTERIMP_H

#include "WAVFileSetter.h"

#include "../aquila/include/aquila/source/WaveFile.h"
class WAVFileSetterImp : public WAVFileSetter {
private:
    std::string fileName;

public:
    WAVFileSetterImp();
    virtual ~WAVFileSetterImp();
    void setFileName(std::string fileName);
    std::string getFileName();

};


#endif //VOICEACTIVITYDETECTION_WAVFILESETTERIMP_H
