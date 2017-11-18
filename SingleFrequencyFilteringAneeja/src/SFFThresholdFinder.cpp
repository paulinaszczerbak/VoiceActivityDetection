//
// Created by paulina on 17.11.17.
//

#include <algorithm>
#include <iostream>
#include "../inc/SFFThresholdFinder.h"

using namespace std;

SFFThresholdFinder::SFFThresholdFinder() {

}

SFFThresholdFinder::~SFFThresholdFinder() {

}
/***
 * Function which counts threshold for specific utterance
 * @param wav - sampled utterance for which threshold will be counted
 * @return threshold
 */
double SFFThresholdFinder::countThreshold(Aquila::SignalSource& wav) {

    //posortowac od najmniejszych wart
    vector<Aquila::SampleType> sortedWAV(wav.begin(), wav.end());
    sort(sortedWAV.begin(), sortedWAV.end());

    //wybrac 20% kolejnych probek
    int amountOfSamples = 0.2*wav.getSamplesCount();
    vector<Aquila::SampleType> sortedWAVSplited(sortedWAV.begin(), sortedWAV.begin()+amountOfSamples);
//    cout << "myvector contains:";
//    for (std::vector<Aquila::SampleType>::iterator it=sortedWAVSplited.begin(); it!=sortedWAVSplited.end(); ++it)
//        cout << ' ' << *it;
//    std::cout << '\n';
    //theta = mi_theta + 3*sigma_theta
    return 0;
}


