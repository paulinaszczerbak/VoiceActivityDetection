
#include <iostream>
#include <algorithm>
#include <cstddef>

#include "../aquila/include/aquila/source/WaveFile.h"
#include "../aquila/include/aquila/tools/TextPlot.h"
#include "../aquila/include/aquila/source/FramesCollection.h"
#include "../aquila/include/aquila/source/PlainTextFile.h"

#include "aquila/transform/FftFactory.h"
#include "../inc/VADImp.h"
#include "../inc/ResultPlotter.h"
#include "../inc/SFFDetector.h"

int main()
{


    //Aquila::WaveFile wav("../../odonnell_you_go_girl.wav");
    //Aquila::WaveFile wav("../../harvey_super_cool.wav");
    //Aquila::WaveFile wav("../../miller_larry.wav");
    //Aquila::WaveFile wav("../../carlin_pc.wav");
    //Aquila::WaveFile wav("../../ireland_ouch.wav");
    Aquila::WaveFile wav("../../mbi02w1.wav");
    //Aquila::WaveFile wav("../kabanos.wav");
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

    SFFDetector *detector = new SFFDetector("../../mbi02w1.wav");
    detector->detect();


    return 0;
}
