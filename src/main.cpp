
#include <iostream>
#include <algorithm>
#include <cstddef>
#include <cstdlib>

#include "../aquila/include/aquila/source/WaveFile.h"
#include "../aquila/include/aquila/tools/TextPlot.h"
#include "../aquila/include/aquila/source/FramesCollection.h"
#include "../aquila/include/aquila/source/PlainTextFile.h"


#include "../inc/VADImp.h"
#include "../inc/VAD.h"

int main()
{

    //Aquila::WaveFile wav("../../ireland_ouch.wav");
    Aquila::WaveFile wav("../kabanos.wav");
    std::cout << "Filename: "           << wav.getFilename();
    std::cout << "\nLength: "           << wav.getAudioLength()     << " ms";
    std::cout << "\nSample frequency: " << wav.getSampleFrequency() << " Hz";
    std::cout << "\nChannels: "         << wav.getChannelsNum();
    std::cout << "\nByte rate: "        << wav.getBytesPerSec()/1024 << " kB/s";
    std::cout << "\nBits per sample: "  << wav.getBitsPerSample() << "b\n";


    VAD *vad = new VADImp();
    vad->detect(wav,1);

    system("touch sigToPlot");
    Aquila::PlainTextFile::save(wav, "sigToPlot");
    system("gnuplot gnuscript.pg");



    return 0;
}
