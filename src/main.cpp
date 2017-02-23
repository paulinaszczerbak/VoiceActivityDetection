
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

int main()
{


    //Aquila::WaveFile wav("../../odonnell_you_go_girl.wav");
    //Aquila::WaveFile wav("../../harvey_super_cool.wav");
    //Aquila::WaveFile wav("../../miller_larry.wav");
    Aquila::WaveFile wav("../../carlin_pc.wav");
    //Aquila::WaveFile wav("../../ireland_ouch.wav");
    //Aquila::WaveFile wav("../kabanos.wav");
    std::cout << "Filename: "           << wav.getFilename();
    std::cout << "\nLength: "           << wav.getAudioLength()     << " ms";
    std::cout << "\nSample frequency: " << wav.getSampleFrequency() << " Hz";
    std::cout << "\nChannels: "         << wav.getChannelsNum();
    std::cout << "\nByte rate: "        << wav.getBytesPerSec()/1024 << " kB/s";
    std::cout << "\nBits per sample: "  << wav.getBitsPerSample() << "b\n";


    VAD *vad = new VADImp();
    vad->detect(wav,1);

    ResultPlotter result;
    result.plot(wav);


    return 0;
}
