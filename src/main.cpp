
#include <iostream>
#include <algorithm>
#include <cstddef>
#include <fstream>

#include "../aquila/include/aquila/source/WaveFile.h"
#include "../aquila/include/aquila/tools/TextPlot.h"
#include "../aquila/include/aquila/source/FramesCollection.h"
#include "../aquila/include/aquila/source/PlainTextFile.h"

#include "aquila/transform/AquilaFft.h"
#include "../inc/VADImp.h"
#include "../inc/ResultPlotter.h"
//#include "../inc/SFFDetector.h"
#include "../SingleFrequencyFilteringMc/inc/SFFDetector.h"
#include "../SingleFrequencyFilteringAneeja/inc/Detector.h"
#include "../SingleFrequencyFilteringAneejaChanged/inc/NewDetector.h"
#include "../inc/EnergyBasedDetector.h"


int main()
{
//    Aquila::WaveFile wav("../../odonnell_you_go_girl.wav");
//    Aquila::WaveFile wav("../../harvey_super_cool.wav");
    //Aquila::WaveFile wav("../../miller_larry.wav");
//    Aquila::WaveFile wav("../../carlin_pc.wav");
//    Aquila::WaveFile wav("../../ireland_ouch.wav");
//    Aquila::WaveFile wav("../../mbi04w1.wav");
//    Aquila::WaveFile wav("../kabanos.wav");
//    Aquila::WaveFile wav("../../dbi03kaban.wav");
//    Aquila::WaveFile wav("../../dbi09w1short.wav");
//    Aquila::WaveFile wav("../../mbi04zapam.wav");
//    Aquila::WaveFile wav("../../mbi04poprzedni.wav");
//    Aquila::WaveFile wav("../../eastwood_lawyers.wav");
//    Aquila::WaveFile wav("../../mbi02w1.wav");
//    Aquila::WaveFile wav("../../mbi04w1.wav");
//    Aquila::WaveFile wav("../../dbi03w1s14.wav");
    Aquila::WaveFile wav("../../mwr35w1s14.wav");




    std::cout << "Filename: "           << wav.getFilename();
    std::cout << "\nLength: "           << wav.getAudioLength()     << " ms";
    std::cout << "\nSample frequency: " << wav.getSampleFrequency() << " Hz";
    std::cout << "\nChannels: "         << wav.getChannelsNum();
    std::cout << "\nByte rate: "        << wav.getBytesPerSec()/1024 << " kB/s";
    std::cout << "\nBits per sample: "  << wav.getBitsPerSample() << "b";
    std::cout << "\nSamples: "          << wav.getSampleFrequency()*wav.getAudioLength()/1000  << " samples\n";
//    for (int i = 0; i <wav.getSamplesCount() ; ++i) {
//        std::cout<<wav.sample(i)<<" ";
//    }

//    VAD *vad = new VADImp();
//    vad->detect(wav,1);
//
//    ResultPlotter *result = new ResultPlotter();
//    result->plot(wav);

    EnergyBasedDetector *detector = new EnergyBasedDetector();
    detector->detect(wav);

    Detector detectorSFF;
    detectorSFF.detect(wav);

    NewDetector detectorSFFNew;
    detectorSFFNew.detect(wav);



//    AquilaFft spectrum(wav.getSamplesCount());
//    const SampleType* x = wav.toArray();
//    SpectrumType mySpectrum;
//    mySpectrum = spectrum.fft(x);
//
//    //writing to file to plot results
//    system("touch spectrum");
//    //otwieram plik do zapisu
//    ofstream file2("spectrum");
//    if(file2){
//        for (size_t i = 0; i< mySpectrum.size() ; i++) {
//            file2 << mySpectrum.at(i) << endl;
//        }
//        file2.close();
//    } else{
//        cout<<"BLAD: nie mozna otworzyc pliku"<<endl;
//    }

    return 0;
}
