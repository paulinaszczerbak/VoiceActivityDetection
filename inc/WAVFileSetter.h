//
// Created by paulina on 15.02.17.
//interfejs do ustawiania nazwy przetwarzanego pliku
//
#include <iostream>

#ifndef VOICEACTIVITYDETECTION_WAVFILESETTER_H
#define VOICEACTIVITYDETECTION_WAVFILESETTER_H



class WAVFileSetter {
private:
    std::string fileName;
public:
    WAVFileSetter();
    virtual ~WAVFileSetter();
    virtual void setFileName(std::string fileName)=0;
    const std::string getFileName();

};


#endif //VOICEACTIVITYDETECTION_WAVFILESETTER_H
