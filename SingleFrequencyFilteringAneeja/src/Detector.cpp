//
// Created by paulina on 17.11.17.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <aquila/source/FramesCollection.h>
#include "../inc/Detector.h"
using namespace Aquila;


Detector::Detector() {

}

Detector::~Detector() {
}


/***
 * Detect if there is speech or nonspeech
 * @param wav - detecting signal
 */
void Detector::detect(SignalSource& wav) {
    _samplingFrequency = wav.getSampleFrequency();
    double weight(0);
    int normalizedFrequency = 3200;
    ///add some gaussian noise
    SignalSource wavNoised = addGaussianNoiseToSignal(wav);
    ///count SFFEnvelopes for 185 frequencies 300-4000Hz by 20Hz
    int beginFrequency = 300;
    int endFrequency = 4001;
    int interval = 20;
    ///delta - corresponding to the article
    vector<SampleType> delta = countSFFEnvelopesForFrequencies(wavNoised, beginFrequency, endFrequency, interval);

    double threshold = countThreshold(delta);

    ///count DYNAMIC RANGE
    /// count ro = 10*log10 * (max_m(E_m))/(min_m(E_m)) - dynamic range
    /// it's needed to count smoothing window l_w
    double ro = countDynamicRange(wavNoised);
    cout<<"ro"<<ro<<endl;
    ///set window size - corresponding to dynamic range value
    double windowSize = countWindowSize(ro);

    ///DECISION LOGIC AT EACH SAMPLING INSTANT
    ///the values of delta(n) are averaged over a window of size l_w to obtain the averaged
    /// value delta(n) at each sample index n
    vector<SampleType> deltaAveraged = averageVector(delta, windowSize);
    SignalSource deltaSignal = vectorToSignalSource(deltaAveraged);
//    vector<short> decision = makeDecisionAtSampleLevel(deltaAveraged, threshold);
//    vector<short> smoothedDecision = smoothDecision(decision, windowSize);

    //DECISION LOGIC AT EACH FRAME
    vector<short> decision = makeDecisionAtFrameLevel(deltaSignal, threshold);

    cout<<"decision"<<decision.size()<<endl;
    cout<<"wav"<<wav.getSamplesCount()<<endl;

    //writing to file to plot results
    system("touch signalToPlot");
    //otwieram plik do zapisu
    ofstream file1("signalToPlot");
    if(file1){
        for (size_t i = 0; i< wavNoised.getSamplesCount() ; i++) {
            file1 << wavNoised.sample(i) << endl;
        }
        file1.close();
    } else{
        cout<<"BLAD: nie mozna otworzyc pliku"<<endl;
    }

    //writing to file to plot results
    system("touch ResultDecisionToPlot");
    //otwieram plik do zapisu
    ofstream file2("ResultDecisionToPlot");
    if(file2){
        for (size_t i = 0; i< decision.size() ; i++) {
            file2 << decision[i] << endl;
        }
        file2.close();
    } else{
        cout<<"BLAD: nie mozna otworzyc pliku"<<endl;
    }

}

/***
 * counting Single Frequency Filtering envelope for specific frequency
 * @param wav - signal to process
 * @param normalizedFrequency - specific frequency which will be used to complex sine
 * @return
 */
vector<SampleType> Detector::countSFFEnvelope(SignalSource &wav, int normalizedFrequency) {
    //todo: add noise to signal
    //difference the signal
    SignalSource wavDifferenced = differenceSignal(wav);

    //multiply signal x(n) by a complex sinusoid of a given normalized frequency wk
    vector<complex<SampleType>> wavMultipliedByComplexSinusoid = MultipyByComplexSinusoid(wavDifferenced, normalizedFrequency);

    //count output yk(n) = -r*yk(n-1) +xk(n)
    vector<complex<double>> wavFilterOutput= countFilterOutput(wavMultipliedByComplexSinusoid);

    //count envelope
    vector<SampleType> wavEnvelope = countEnvelope(wavFilterOutput);

    return wavEnvelope;
}


/***
 * Function to calculate signal denoted by x(n) = s(n) - s(n-1)
 * @param wav - signal to difference
 * @return
 */
Aquila::SignalSource Detector::differenceSignal(const Aquila::SignalSource &wav) {
    vector<SampleType> wavVector(wav.begin(), wav.end());
    vector<SampleType> wavDifferenced;
    wavDifferenced.push_back(wavVector[0]);
    for (vector<SampleType>::iterator it=wavVector.begin()+1; it!=wavVector.end(); ++it){
        wavDifferenced.push_back(*it - *(it-1));
    }

    return SignalSource(wavDifferenced, wav.getSampleFrequency());
}


/**
 * multiplies signal by complex sinusoid
 * @param source - wav signal
 * @param frequency - signal sampling frequency
 * @return
 */
vector<complex<SampleType>> Detector::MultipyByComplexSinusoid(const SignalSource& wav, int normalizedFrequency) {

    vector<SampleType> wavVector(wav.begin(), wav.end());
    vector<complex<SampleType>> result;
    //complex sinusoid
    const double pi = acos(-1);
    const complex<double> j(0, 1);


    double omega_k = (2*pi*normalizedFrequency)/wav.getSampleFrequency();
    for (vector<SampleType>::iterator it=wavVector.begin(); it!=wavVector.end(); ++it){
        long index = std::distance(wavVector.begin(), it);
        //exp(j*sr_omega_k*n)
        result.push_back(*it*exp(j*omega_k*(double)index));
    }

    return result;
}

/***
 * Single-pole filter has a pole on the real axis at a distance of r from the origin.
 * the location of the root is at z=-r in the z-plane, which corresponds to half the sampling
 * frequency fs/2
 * The output of the filter is given by
 * yk(n) = -r*yk(n-1) +xk(n)
 * @param wav - vector to filter
 * @return
 */
vector<complex<double>> Detector::countFilterOutput(vector<complex<SampleType>> &wav) {
//    const double root = 0.97; //prof.
    const double root = 0.99;   //article

    vector<complex<double>> output;
    //y(0)=0
    output.push_back((0.0,0.0));

    //iterating starts at index=1, because we use output[index-1]
    for (vector<complex<SampleType>>::iterator signalSample=wav.begin()+1; signalSample!=wav.end(); ++signalSample){
        unsigned long currentIndex = (unsigned long)distance(wav.begin(), signalSample);
        output.push_back(output.at(currentIndex-1) *(-root) + *signalSample);
    }


    return output;
}

/***
 * Function counting values for signal's envelope
 * @param complexSignal - signal with complex samples
 * @return
 */
vector<SampleType> Detector::countEnvelope(vector<complex<double>> &complexSignal) {
    vector<SampleType> envelope;
    for (vector<complex<SampleType>>::iterator signalSample=complexSignal.begin(); signalSample!=complexSignal.end(); ++signalSample){
        unsigned long currentIndex = (unsigned long)distance(complexSignal.begin(), signalSample);
        envelope.push_back(sqrt((*signalSample).real()*(*signalSample).real() + (*signalSample).imag()*(*signalSample).imag()));
    }
    //normalize envelope values

    return envelope;
}

double Detector::countWeightValue(vector<SampleType> envelope ) {
    //sort envelope values to get 20% of the lowest (20% from the beginning)
    sort(envelope.begin(), envelope.end());

    //get 20% first samples
    int amountOfSamples = (int)(envelope.size()*0.2);
    vector<SampleType> splitedEnvelope(envelope.begin(), envelope.begin()+amountOfSamples);

    //mean of the lower 20% of the values of the envelope
    double average = accumulate( splitedEnvelope.begin(), splitedEnvelope.end(), 0.0)/splitedEnvelope.size();

    return 1/average;
}

vector<SampleType> Detector::scaleSignal(vector<SampleType> wavEnvelope, double weight) {
    //multiply vector by scalar
    std::transform(wavEnvelope.begin(), wavEnvelope.end(), wavEnvelope.begin(),
                   std::bind1st(std::multiplies<SampleType>(), weight));
    return wavEnvelope;
}

/***
 * [Note: Seeding from std::random_device is a good practice to get into;
 * if you use the current time as a seed, you can end up with the same seed
 * value across multiple generators (e.g. when initialising several generators
 * in a very short period of time).
 * std::random_device will obtain entropy from the system, if available
 * @param signal
 * @return
 */
SignalSource Detector::addGaussianNoiseToSignal(SignalSource signal) {

    vector<SampleType> noised(signal.begin(), signal.end());
    // Define random generator with Gaussian distribution
    const double mean = 0.0;
    const double stddev = 0.1;

    auto dist = std::bind(std::normal_distribution<double>{mean, stddev},
                          std::mt19937(std::random_device{}()));

    // Add Gaussian noise
    for (auto& x : noised) {
        x = x + dist();
    }

    return SignalSource(noised, signal.getSampleFrequency());
}

/***
 * Function counting envelopes in for loop for different frequences
 * @param source - signal to count SFF envelope
 * @param beginFrequency - frequency in which we start
 * @param endFrequency - frequency in which we end
 * @param interval - tells how many Hz is between counted frequences
 * @return vector with avearges values of SFF envelopes values' squares
 */
vector<SampleType> Detector::countSFFEnvelopesForFrequencies(SignalSource &source, int beginFrequency, int endFrequency, int interval) {
    //zapisuje do tego wektora sume kwadratow probek
    // - po kazdym policzeniu obwiedni dodaje kolejne probki (wlasciwie to ich kwadraty)
    vector<SampleType> meanSquareEnvelope(source.getSamplesCount(), 0);

    //sum of squares for different frequencies
    for (int frequency = beginFrequency; frequency <endFrequency; frequency=frequency+interval) {
        //count Single Frequency Filtered envelope
        vector<SampleType> SFFEnvelope = countSFFEnvelope(source, frequency);
        //count weight value for specific normalizedFrequency
        double weight = countWeightValue(SFFEnvelope);
        //scale envelope
        vector<SampleType> weightedComponentEnvelope = scaleSignal(SFFEnvelope, weight);

        //count squares of envelope values
        //add squares to meanSquareEnvelope values
        int currentIndex(0);
        for (vector<SampleType>::iterator it=weightedComponentEnvelope.begin(); it!=weightedComponentEnvelope.end(); it++){
            meanSquareEnvelope[currentIndex] += (*it)*(*it);
            currentIndex++;
        }

    }

    int amountOfEnvelopes = (endFrequency-beginFrequency)/interval;
    meanSquareEnvelope = scaleSignal(meanSquareEnvelope, (1.000/amountOfEnvelopes));

    //COUNT STANDARD DEVIATION
    //we need to iterate on frequencies and count everything once again
    //to count standard deviation sigma(n) = sqrt((1/(n-1) * sum(i=1, n, (xi-x_sr)^2)
    vector<SampleType> standardDeviationSquareEnvelope(source.getSamplesCount(), 0);
    for (int frequency = beginFrequency; frequency <endFrequency; frequency=frequency+interval) {
        //count Single Frequency Filtered envelope
        vector<SampleType> SFFEnvelope = countSFFEnvelope(source, frequency);
        //count weight value for specific normalizedFrequency
        double weight = countWeightValue(SFFEnvelope);
        //scale envelope
        vector<SampleType> weightedComponentEnvelope = scaleSignal(SFFEnvelope, weight);

        //count squares of envelope values
        //add squares to meanSquareEnvelope values
        int currentIndex(0);
        double sumOfDeviations(0);
        for (vector<SampleType>::iterator it=weightedComponentEnvelope.begin(); it!=weightedComponentEnvelope.end(); it++){
            //count sum(xi-x_sr)^2
            standardDeviationSquareEnvelope[currentIndex] += ((*it)*(*it) - meanSquareEnvelope[currentIndex])*((*it)*(*it) - meanSquareEnvelope[currentIndex]);
            currentIndex++;
        }

    }
//    standardDeviationSquareEnvelope[currentIndex]
//        = sqrt((1/(currentIndex-1)) * sumOfDeviations);
    //multiply sum of squares by 1/(n-1)
    standardDeviationSquareEnvelope = scaleSignal(standardDeviationSquareEnvelope, 1.000/(amountOfEnvelopes-1));
    for (auto& x : standardDeviationSquareEnvelope) {
        x = sqrt(x);
    }

    //todo: count dela(n) = sqrt(abs(sigma^2(n) - ni^2(n)),M), where sigma = standard deviation, ni = mean,
    // M should be in range 32 to 256
    vector<SampleType> delta(source.getSamplesCount(), 0);
    int sqrtLevel = 64;
    int currentIndex(0);
    for (int i = 0; i < delta.size() ; i++) {
        delta[i] = pow(abs((standardDeviationSquareEnvelope[i]*standardDeviationSquareEnvelope[i])
        - (meanSquareEnvelope[i]*meanSquareEnvelope[i])), 1.0/sqrtLevel);
    }


    return delta;
}

/***
 * Compute the mean (mi_theta) and the wariance (sigma_theta) of the lower 20% of the values of delta(n) over an utterance
 * A threshold of theta = mi_theta + 3*sigma_theta is used in all cases.
 * The theta value depends on each utterance
 * @param delta
 * @return
 */
double Detector::countThreshold(vector<SampleType> delta) {
    //sort delta and get 20% first values
//    vector<SampleType> test = {3,5,3,3,5,6,4,2,1,8};
    sort(delta.begin(), delta.end());
    //get 20% first samples
    int amountOfSamples = (int)(delta.size()*0.2);
    vector<SampleType> splitedDelta(delta.begin(), delta.begin()+amountOfSamples);
    //todo: count mean and varinace for splitedDelta
//    double mean(0);
    //mean - maybe is there any function in stl??
//    for(auto& x : splitedDelta){
//        mean += x;
//    }
    double mean = accumulate( splitedDelta.begin(),
                                 splitedDelta.end(),
                                 0.0)/splitedDelta.size();
//    mean=mean/splitedDelta.size();
    //variance: ((1/(n-1) * sum(i=1, n, (xi-x_sr)^2)
    double variance(0);
    for(auto& x : splitedDelta){
        variance += (x-mean)*(x-mean);
    }
    variance = variance/splitedDelta.size();
    //threshold theta
    double threshold = mean + 3*variance;

    return threshold;
}

double Detector::countDynamicRange(SignalSource source) {
    //count energy of the signal (source) - energy  is computed over a frame of 300msec for a frame shift
    //of 10msec, where m is the frame index
    vector<double> signalEnergyPerEachFrame = countSignalEnergyPerFrame(source);

    //find max and min energy
    double maxEnergy = *max_element(signalEnergyPerEachFrame.begin(), signalEnergyPerEachFrame.end());
    double minEnergy = *min_element(signalEnergyPerEachFrame.begin(), signalEnergyPerEachFrame.end());

    //count dynamic range: ro = 10*log10 ((max_m(E_m))/(min_m(E_m)))
    double dynamicRange = 10* log10(maxEnergy/minEnergy);
    return dynamicRange;
}

vector<double> Detector::countSignalEnergyPerFrame(SignalSource source) {
    double frameLengthInSecs = 0.3;
    double shiftLengthInSecs = 0.1;
    unsigned int samplesPerFrame = (unsigned int) (source.getSampleFrequency() * frameLengthInSecs);
    unsigned int samplesInShift = (unsigned int) (source.getSampleFrequency() * shiftLengthInSecs);
    unsigned int commonSamples = samplesPerFrame-samplesInShift;
    vector<double> signalFramesEnergy;
    FramesCollection frames(source, samplesPerFrame, commonSamples);
    for (auto& frame : frames){
        signalFramesEnergy.push_back(countSingleFrameEnergy(frame));
    }

    return signalFramesEnergy;
}

double Detector::countSingleFrameEnergy(Frame &frame) {
    double energy(0);
    for (SignalSource::iterator sample=frame.begin(); sample!=frame.end(); sample++){
        energy += (*sample)*(*sample);
    }
    energy=energy/frame.getSamplesCount();

    return energy;

}

/***
 * Sets _windowSize as it is said in the article (in msec)
 * @param ro
 */
double Detector::countWindowSize(double ro) {
    double windowSize;
    if (ro<30){
        windowSize=0.4;
    }
    else if(ro>=30 && ro<=40){
        windowSize=0.3;
    }
    else if(ro>40){
        windowSize=0.2;
    }
    return windowSize;
}

/***
 *
 * @param vectorToAverage
 * @param windowSize
 * @return
 */
vector<SampleType> Detector::averageVector(vector<SampleType>& vectorToAverage, double windowSize) {
    vector<SampleType> averaged = vectorToAverage;

    int samplesPerWindow = (int)(_samplingFrequency * windowSize);
    if(samplesPerWindow%2 == 0){
        samplesPerWindow += 1;
    }
    int halfOfSamplesPerWindow = (samplesPerWindow-1)/2;
    for (vector<SampleType>::iterator it=averaged.begin()+halfOfSamplesPerWindow;
         it!=averaged.end()-halfOfSamplesPerWindow;
         it++){
        double average = accumulate( it-halfOfSamplesPerWindow,
                                     it+halfOfSamplesPerWindow+1,
                                     0.0)/samplesPerWindow;
        *it=average;
    }
    return averaged;
}

vector<short> Detector::makeDecisionAtSampleLevel(vector<SampleType>& averagedVector, double threshold) {
    vector<short> decision;
    for(auto& sample : averagedVector){
        if (sample > threshold){
            decision.push_back(1);
        } else{
            decision.push_back(0);
        }
    }

    return decision;
}

vector<short> Detector::smoothDecision(vector<short>& decision, double windowSize) {
    vector<short> smoothedDecision = decision;
    double threshold = 0.6;
    double tempWindowSize(0.3);
    int samplesPerWindow = (int)(_samplingFrequency * tempWindowSize);
//    samplesPerWindow=100;
    if(samplesPerWindow%2 == 0){
        samplesPerWindow += 1;
    }

    int halfOfSamplesPerWindow = (samplesPerWindow-1)/2;

//    for (vector<short>::iterator it=smoothedDecision.begin()+101;
//         it!=smoothedDecision.begin()+halfOfSamplesPerWindow;
//         it++){
//        double sumInWindow = accumulate( it-100,
//                                         it+101,
//                                         0.0);
//
//        if(sumInWindow > 0.6*201){
//            *it = 1;
//        } else{
//            *it = 0;
//        }
//
//    }

    for (vector<short>::iterator it=smoothedDecision.begin()+halfOfSamplesPerWindow;
         it!=smoothedDecision.end()-halfOfSamplesPerWindow;
         it++){
        double sumInWindow = accumulate( it-halfOfSamplesPerWindow,
                                     it+halfOfSamplesPerWindow+1,
                                     0.0);

        if(sumInWindow > 0.6*samplesPerWindow){
            *it = 1;
        } else{
            *it = 0;
        }

    }
    return smoothedDecision;
}

/***
 * The decision is given for every 10 msec frame. For each 10 msec nonoverlapping
 * frame, if majority of d_f(n) is converted to a 10 msec frame based decision.
 * @param delta
 * @return
 */
vector<short> Detector::makeDecisionAtFrameLevel(const SignalSource& delta, double threshold) {
    cout<<"delta"<<delta.getSamplesCount()<<endl;
    vector<short> decision;

    double frameLengthInSecs = 0.01;
    unsigned int samplesPerFrame = (unsigned int) (_samplingFrequency * frameLengthInSecs);
    FramesCollection frames(delta, samplesPerFrame);
    for (FramesCollection::iterator frame=frames.begin(); frame!=frames.end(); frame++){
        int speechCounter(0);
        for (SignalSource::iterator sample=(*frame).begin(); sample!=(*frame).end(); sample++){
            if(*sample > threshold) {
                speechCounter++;
            }
        }
        cout<<speechCounter<<endl;
        if (speechCounter > 0.6*samplesPerFrame){
            for(SignalSource::iterator sample=(*frame).begin(); sample!=(*frame).end(); sample++){
                decision.push_back(1);
            }
        } else{
            for(SignalSource::iterator sample=(*frame).begin(); sample!=(*frame).end(); sample++){
                decision.push_back(0);
            }
        }
    }

    return decision;
}



SignalSource Detector::vectorToSignalSource(vector<SampleType> vectorToConvert) {
    return SignalSource(vectorToConvert);
}


