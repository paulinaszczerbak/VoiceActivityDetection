
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstddef>

#include "../aquila/include/aquila/source/WaveFile.h"
#include "../aquila/include/aquila/tools/TextPlot.h"
#include "../aquila/include/aquila/source/FramesCollection.h"
#include "../aquila/include/aquila/transform/Spectrogram.h"
#include "../aquila/include/aquila/transform/OouraFft.h"

int main()
{

    Aquila::WaveFile wav("../kabanos.wav");
    std::cout << "Filename: "           << wav.getFilename();
    std::cout << "\nLength: "           << wav.getAudioLength()     << " ms";
    std::cout << "\nSample frequency: " << wav.getSampleFrequency() << " Hz";
    std::cout << "\nChannels: "         << wav.getChannelsNum();
    std::cout << "\nByte rate: "        << wav.getBytesPerSec()/1024 << " kB/s";
    std::cout << "\nBits per sample: "  << wav.getBitsPerSample() << "b\n";

    int samplesPerFrame(10);
    int commonSamples(5);
    Aquila::FramesCollection frames(wav, samplesPerFrame,commonSamples);
    std::cout<<"liczba ramek:"<<frames.count()<<std::endl;
    std::cout<<"liczba probek w ramce:"<<frames.getSamplesPerFrame()<<std::endl;
    float energy(0);
    //obliczam energie w jednej, konkretnej ramce
    for(int i=0; i<frames.getSamplesPerFrame();i++){
        //iteruje po probkach w ramce
        std::cout<<frames.frame(14000).sample(i)<<std::endl;
        energy=energy+(frames.frame(14000).sample(i)*frames.frame(14000).sample(i));
    }
    energy=energy/frames.getSamplesPerFrame();
    std::cout<<"Energia ramki nr 15000: "<<energy<<std::endl;


    //Aquila::Spectrogram spec(frames);

    return 0;
}
