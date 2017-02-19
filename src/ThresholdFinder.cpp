//
// Created by paulina on 06.02.17.
//

#include "../inc/ThresholdFinder.h"
#define THRESHOLD 300

ThresholdFinder::ThresholdFinder() {
    this->threshold=THRESHOLD;
}

void ThresholdFinder::setThreshold(float threshold) {
    this->threshold=threshold;
}

float ThresholdFinder::getThreshold() {
    return this->threshold;
}

