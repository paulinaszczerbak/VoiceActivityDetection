//
// Created by paulina on 17.11.17.
//

#ifndef VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
#define VOICEACTIVITYDETECTION_THRESHOLDFINDER_H

#include <aquila/source/WaveFile.h>

/**
 * Class used to compute threshold (theta)
 * theta = mi_theta + 3*sigma_theta
 * mi_theta - mean value of the lower 20% of the values of delta(n) (signal) over an utterance
 * sigma_theta - variance of the lower 20% of the values of delta(n) (signal) over an utterance
 *
 */

class SFFThresholdFinder {
private:

public:
    SFFThresholdFinder();
    virtual ~SFFThresholdFinder();
    double countThreshold(Aquila::SignalSource& wav);
};


#endif //VOICEACTIVITYDETECTION_THRESHOLDFINDER_H
