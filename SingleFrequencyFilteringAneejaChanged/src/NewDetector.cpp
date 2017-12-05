//
// Created by paulina on 17.11.17.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <aquila/source/FramesCollection.h>
#include "../inc/NewDetector.h"
using namespace Aquila;


NewDetector::NewDetector() {

}

NewDetector::~NewDetector() {
}


/***
 * Detect if there is speech or nonspeech
 * @param wav - detecting signal
 */
void NewDetector::detect(SignalSource& wav) {
    _samplingFrequency = wav.getSampleFrequency();
    double weight(0);
    int normalizedFrequency = 3200;
    ///add some gaussian noise
    SignalSource wavNoised = addGaussianNoiseToSignal(wav, 0.0001);
    ///count SFFEnvelopes for 185 frequencies 300-4000Hz by 20Hz
    int beginFrequency = 300;
    int amountOfFrequencies = 186;
    int interval = 20;

    ///difference the signal - it's part of counting SFFenvelope, but it's the same base for all
    SignalSource wavDifferenced = differenceSignal(wavNoised);
    ///delta - corresponding to the article
    vector<SampleType> delta = countSFFEnvelopesForFrequencies(wavDifferenced, beginFrequency, amountOfFrequencies, interval);
    int amountOfLoops(20);
    delta = smoothSignal(delta, amountOfLoops);

    ///THRESHOLD BETA
    double thresholdBeta = countThresholdBeta(delta);
    double thresholdTheta = countThresholdTheta(delta);
    //TODO BETAMULTIPLICATION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    double betaMultiplication = 1.0;
    thresholdBeta *= betaMultiplication;
    cout<<"thresholdBeta"<<thresholdBeta<<endl;
    cout<<"thresholdTheta "<<thresholdTheta<<endl;

    SignalSource deltaSignal = vectorToSignalSource(delta);
    ///DECISION LOGIC AT EACH SAMPLING INSTANT
    ///the values of delta(n) are averaged over a window of size l_w to obtain the averaged
    /// value delta(n) at each sample index n
//    vector<short> decision = makeDecisionAtSampleLevel(deltaAveraged, threshold);
//    vector<short> smoothedDecision = smoothDecision(decision, windowSize);
    ///DECISION LOGIC AT EACH FRAME
    vector<short> decision = makeDecisionAtFrameLevel(deltaSignal, thresholdBeta);
    decision[0]=0;
    decision[decision.size()-1]=0;

    //writing to file to plot results
    system("touch signalToPlotNewDetector");
    //otwieram plik do zapisu
    ofstream file1("signalToPlotNewDetector");
    if(file1){
        for (size_t i = 0; i< wavNoised.getSamplesCount() ; i++) {
            file1 << wavNoised.sample(i) << endl;
        }
        file1.close();
    } else{
        cout<<"BLAD: nie mozna otworzyc pliku"<<endl;
    }

    //writing to file to plot results
    system("touch ResultToPlotNewDetector");
    //otwieram plik do zapisu
    ofstream file2("ResultToPlotNewDetector");
    if(file2){
        for (size_t i = 0; i< decision.size(); i++) {
            file2 << decision.at(i) << endl;
        }
        file2.close();
    } else{
        cout<<"BLAD: nie mozna otworzyc pliku"<<endl;
    }

}

/***
 * counting Single Frequency Filtering envelope for specific frequency
 * different type for counting envelope
 * @param wav - signal to process
 * @param normalizedFrequency - specific frequency which will be used to complex sine
 * @return
 */
vector<SampleType> NewDetector::countSingleSFFEnvelope(SignalSource &wavDifferenced, int normalizedFrequency) {
    vector<SampleType> wavEnvelope;
    const double pi = acos(-1);

    double omega = 2*pi*normalizedFrequency/_samplingFrequency;
    double module = 0.97;       //empirycznie

    ///filter factors
    double amplitude1 = module * cos(omega);
    double amplitude2 = module * sin(omega);

    ///filter initialization
    vector<double> XReal(wavDifferenced.getSamplesCount(), 0);
    vector<double> XImaginary(wavDifferenced.getSamplesCount(), 0);

    ///recursive quadrature filter
    for (int i = 1; i < wavDifferenced.getSamplesCount(); i++) {
        XReal[i] = wavDifferenced.sample(i) + amplitude1 * XReal.at(i-1) - amplitude2 * XImaginary.at(i-1);
        XImaginary[i] = amplitude1 * XImaginary.at(i-1) + amplitude2 * XReal.at(i-1);
    }

    ///envelope
    for (int j = 0; j < wavDifferenced.getSamplesCount(); j++) {
        wavEnvelope.push_back(sqrt(XReal.at(j)*XReal.at(j) * XImaginary.at(j)*XImaginary.at(j)));
    }

//    vector<double>::iterator max = max_element(wavEnvelope.begin(), wavEnvelope.end());
//    long maxIndex = std::distance(wavEnvelope.begin(), max);
    double max = *max_element(wavEnvelope.begin(), wavEnvelope.end());
    vector<double> envelopeDensity = countDensityForPositiveValues(wavEnvelope, 801, max);

    ///threshold - silence - looking for 20%(here 15%) of lower values
    double firstThreshold = 0.2;
    double sumOfSamples(0.0);
    int k;
    for (k = 0; k < 801; k++) {
        sumOfSamples += envelopeDensity[k];
        if (sumOfSamples>firstThreshold) break;
    }

    double distance = max / 800;
    double secondThreshold = k * distance + distance/2;

    ///mean for 'silence'
    sumOfSamples = 0;
    long position(0);
    for (int k = 0; k < wavDifferenced.getSamplesCount(); k++) {
        if (wavEnvelope[k] < secondThreshold){
            sumOfSamples += wavEnvelope[k];
            position++;
        }
    }
    if (position > 0){
        sumOfSamples = sumOfSamples/position;
    } else{
        sumOfSamples = 0.1 * distance;
    }

    ///envelope weightening
    sumOfSamples *= 32768;
    for (int i = 0; i < wavEnvelope.size(); i++) {
        wavEnvelope[i] = wavEnvelope[i]/sumOfSamples;
    }

    return wavEnvelope;
}


/***
 * Function to calculate signal denoted by x(n) = s(n) - s(n-1)
 * @param wav - signal to difference
 * @return
 */
Aquila::SignalSource NewDetector::differenceSignal(const Aquila::SignalSource &wav) {
    vector<SampleType> wavVector(wav.begin(), wav.end());
    vector<SampleType> wavDifferenced;
    wavDifferenced.push_back(wavVector[0]);
    for (vector<SampleType>::iterator it=wavVector.begin()+1; it!=wavVector.end(); ++it){
        wavDifferenced.push_back(*it - *(it-1));
    }

    return SignalSource(wavDifferenced, wav.getSampleFrequency());
}


double NewDetector::countWeightValue(vector<SampleType> envelope ) {
    //sort envelope values to get 20% of the lowest (20% from the beginning)
    sort(envelope.begin(), envelope.end());

    //get 20% first samples
    int amountOfSamples = (int)(envelope.size()*0.2);
    vector<SampleType> splitedEnvelope(envelope.begin(), envelope.begin()+amountOfSamples);

    //mean of the lower 20% of the values of the envelope
    double average = accumulate( splitedEnvelope.begin(), splitedEnvelope.end(), 0.0)/splitedEnvelope.size();

    return 1/average;
}

vector<SampleType> NewDetector::scaleSignal(vector<SampleType> wavEnvelope, double weight) {
    //multiply vector by scalar
    std::transform(wavEnvelope.begin(), wavEnvelope.end(), wavEnvelope.begin(),
                   std::bind1st(std::multiplies<SampleType>(), weight));
    return wavEnvelope;
}

/***
 * Adding noise to signal based on clock
 * @param signal
 * @return noised signal
 */
SignalSource NewDetector::addGaussianNoiseToSignal(const SignalSource& signal, double noiseMultiplication) {
    //zmienne lokalne do wygenerowania szumu
    clock_t  timer;
    //RAND_MAX - maksymalna wartosc zwrocona przez rand()
    long centr = RAND_MAX/2;
    long random1(0), random2(0);
    vector<Aquila::SampleType> samplesNoised;

    timer = clock();
    srand(timer);
    for (long i = 0; i < signal.getSamplesCount() ; i++) {
        random1=0;
        for (int j = 0; j < 16 ; j++) {
            random2 = rand();
            random1 += random2 - centr;
        }
        //dodatkowe dzielenie w przypadku kompilatora 64-bitowego
        random1 /= 65536;
        random1 /= 8;
        //_signal->samplesNoised[i] = _signal->samplesOriginal[i] + noiseMult * random1;
        samplesNoised.push_back(signal.sample(i) + noiseMultiplication * random1);
    }
    return SignalSource(samplesNoised, signal.getSampleFrequency());

}

/***
 * Function counting envelopes in for loop for different frequences
 * To speed up computations, we can bypass some frequencies
 * First, we count every fourth frequency
 * @param source - signal to count SFF envelope
 * @param beginFrequency - frequency in which we start
 * @param endFrequency - frequency in which we end
 * @param interval - tells how many Hz is between counted frequences
 * @return vector with avearges values of SFF envelopes values' squares
 */
vector<SampleType> NewDetector::countSFFEnvelopesForFrequencies(SignalSource &source, int beginFrequency, int interval, int amountOfFrequencies) {

    amountOfFrequencies=186;
    interval = 20;
    int amountOfComputedFrequencies(0);
    int frequency(0);
    double sample(0), mean(0), standardDeviation(0);
    vector<SampleType> wavEnvelope;
    vector<SampleType> mi(source.getSamplesCount(), 0);
    vector<SampleType> sigma(source.getSamplesCount(), 0);
    vector<SampleType> delta;

    //problem with computing variance
    for (int i = 0; i < amountOfFrequencies ; i+=4) {
        frequency = beginFrequency + i*interval;
        wavEnvelope = countSingleSFFEnvelope(source, frequency);
        amountOfComputedFrequencies++;
        for (int j = 0; j < wavEnvelope.size(); j++) {
            //energy
            sample = wavEnvelope.at(j);
            sample *= sample;           //kwadrat obwiedni

            mi[j] += sample;
            mean = mi[j]/amountOfComputedFrequencies;  //estymata średniej z kwadratu
            standardDeviation = sample - mean;
            standardDeviation *= standardDeviation;
            sigma[j] += standardDeviation;
        }
    }


    for (int i = 2; i < amountOfFrequencies ; i+=4) {
        frequency = beginFrequency + i*interval;
        wavEnvelope = countSingleSFFEnvelope(source, frequency);
        amountOfComputedFrequencies++;
        for (int j = 0; j < wavEnvelope.size(); j++) {
            //energy
            sample = wavEnvelope.at(j);
            sample *= sample;           //kwadrat obwiedni

            mi[j] += sample;
            mean = mi[j]/amountOfComputedFrequencies;  //estymata średniej z kwadratu
            standardDeviation = sample - mean;
            standardDeviation *= standardDeviation;
            sigma[j] += standardDeviation;
        }
    }

    //normalization
    for (int k = 0; k < mi.size() ; k++) {
        mi[k] /= amountOfComputedFrequencies;
        sigma[k] /= amountOfComputedFrequencies;
        sigma[k] = sqrt(sigma[k]);
    }

    //measure
    for (int k = 0; k < sigma.size(); k++) {
        sample = fabs(sigma[k]*sigma[k] - mi[k]*mi[k]);
        delta.push_back(pow(sample, 1.0/64));
    }

    return delta;
}

/***
 * Compute the mean (mi_theta) and the wariance (sigma_theta) of the lower 20% of the values of delta(n) over an utterance
 * A threshold of theta = mi_theta + 3*sigma_theta is used in all cases.
 * The theta value depends on each utterance
 * to count 20% lower vaules we count density for positive values
 * @param delta
 * @return
 */
double NewDetector::countThresholdBeta(vector<SampleType> delta) {
    double maxDelta(0);
    ///density
    maxDelta = *max_element(delta.begin(), delta.end());

    ///to count density we need max VALUE
    unsigned long amountOfDensityPoints(801);
    vector<double> density = countDensityForPositiveValues(delta, amountOfDensityPoints, maxDelta);

    ///smoothing
    int amountOfLoops(20);
    density = smoothSignal(density, amountOfLoops);

    ///left max - in range(200, 600) - based on experience
//    double leftMax = *max_element(density.begin()+200, density.begin()+600);
    double dM(0.0);
    int sM(0);
    for (int i = 200; i < 600; i++) {
        if (density.at(i)>dM){
            dM = density.at(i);
            sM = i;
        }
    }
    int leftMax = sM;
//    cout<<"left"<<leftMax<<endl;
    ///right max - in range(601, 800)
//    double rightMax = *max_element(density.begin()+601, density.begin()+800);
    dM = 0.0;
    sM = 0;
    for (int i = 601; i < 800; i++) {
        if (density.at(i)>dM){
            dM = density.at(i);
            sM = i;
        }
    }
    int rightMax = sM;

//    cout<<"right"<<rightMax<<endl;
    ///minimum between leftMax and rightMax
//    double  minLocal = *min_element(max_element(density.begin()+200, density.begin()+600),
//                                   max_element(density.begin()+601, density.begin()+800));
    //todo: MINIMUM TO INDEX, A TEN MAX WYZEJ, TO WARTOSC???
//    long minLocalIndex = std::distance(density.begin(), min_element(max_element(density.begin()+200, density.begin()+600),
//                                                                    max_element(density.begin()+601, density.begin()+800)));
    dM = 10;
    sM = 0;
    for (int i = leftMax; i < rightMax; i++) {
        if (density.at(i)<dM){
            dM = density.at(i);
            sM = i;
        }
    }
//    cout<<"min"<<sM<<endl;
//    double distance = maxDelta / amountOfDensityPoints;
    double dist = maxDelta / 800;
    cout<<"maxDelta"<<maxDelta<<endl;

    double threshold = sM*dist;

    return threshold;
}

double NewDetector::countDynamicRange(SignalSource source) {
    //count energy of the signal (source) - energy  is computed over a frame of 300msec for a frame shift
    //of 10msec, where m is the frame index
    vector<double> signalEnergyPerEachFrame = countSignalEnergyPerFrame(source);

    //find max and min energy
    double maxEnergy = *max_element(signalEnergyPerEachFrame.begin(), signalEnergyPerEachFrame.end());
    double minEnergy = *min_element(signalEnergyPerEachFrame.begin(), signalEnergyPerEachFrame.end());

    // count dynamic range: ro = 10*log10 ((max_m(E_m))/(min_m(E_m)))
    double dynamicRange = 10* log10(maxEnergy/minEnergy);
    return dynamicRange;
}

vector<double> NewDetector::countSignalEnergyPerFrame(SignalSource source) {
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

double NewDetector::countSingleFrameEnergy(Frame &frame) {
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
double NewDetector::countWindowSize(double ro) {
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
vector<SampleType> NewDetector::averageVector(vector<SampleType>& vectorToAverage, double windowSize) {
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

vector<short> NewDetector::makeDecisionAtSampleLevel(vector<SampleType>& averagedVector, double threshold) {
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

vector<short> NewDetector::smoothDecision(vector<short>& decision, double windowSize) {
    vector<short> smoothedDecision = decision;
    double threshold = 0.6;
    double tempWindowSize(0.3);
    int samplesPerWindow = (int)(_samplingFrequency * tempWindowSize);
//    samplesPerWindow=100;
    if(samplesPerWindow%2 == 0){
        samplesPerWindow += 1;
    }

    int halfOfSamplesPerWindow = (samplesPerWindow-1)/2;

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
 * frame, if majoruty of d_f(n) is converted to a 10 msec frame based decision.
 * @param delta
 * @return
 */
vector<short> NewDetector::makeDecisionAtFrameLevel(const SignalSource& delta, double threshold) {
    vector<short> decision;

    double frameLengthInSecs = 0.01;
    unsigned int samplesPerFrame = (unsigned int) (_samplingFrequency * frameLengthInSecs);
    FramesCollection frames(delta, samplesPerFrame);
    cout<<"samplesPerFrame"<<samplesPerFrame<<endl;
    for (FramesCollection::iterator frame=frames.begin(); frame!=frames.end(); frame++){
        int speechCounter(0);

        for (SignalSource::iterator sample=(*frame).begin(); sample!=(*frame).end(); sample++){
//            cout<<*sample<<endl;
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

SignalSource NewDetector::vectorToSignalSource(vector<SampleType> vectorToConvert) {
    return SignalSource(vectorToConvert);
}

vector<SampleType> NewDetector::smoothSignal(const vector<SampleType>& signal, int loops) {
    vector<double> smoothedSignal = signal;

    for (int j = 0; j < loops; j++) {
        for (int i = 1; i < signal.size()-1; i++) {
            smoothedSignal[i] = smoothedSignal[i-1]*0.25 + smoothedSignal[i]*0.5 + smoothedSignal[i+1]*0.25;
        }
    }
    return smoothedSignal;
}

vector<double>
NewDetector::countDensityForPositiveValues(vector<SampleType> vectorToCount, unsigned long amountOfDensityPoints,
                                           double maxDelta) {
    vector<double> density(amountOfDensityPoints, 0);
    ///norm factor
    double normFactor = (amountOfDensityPoints-1)/maxDelta;     //przedzial wartosci dla jednego slupka
    long densityIndex(0);
    for (int i = 0; i < vectorToCount.size(); i++) {
        densityIndex = (long) floor(normFactor*vectorToCount[i] + 0.5);
        if (densityIndex <= amountOfDensityPoints){
            density[densityIndex]++;
        }
    }

    for (int j = 0; j < amountOfDensityPoints ; j++) {
        density[j] = density[j]/vectorToCount.size();
    }

////    ///histogram
////    const float bucketSize = 0.05;
//    unsigned long numberOfBuckets = 801;//(unsigned long)ceil(1 / bucketSize);
//    double bucketSize = numberOfBuckets/maxDelta;
//    vector<int> histogram(numberOfBuckets, 0);
//    cout<<"histogram"<<histogram.size()<<endl;
//
//    for(int i=0; i<vectorToCount.size(); i++){
//
//        int bucket = (int)floor(vectorToCount[i]/bucketSize);
//
////        cout<<bucket<<endl;
//        histogram[bucket] +=1;
//    }
//
//    for(auto loop = histogram.begin(); loop != histogram.end();++loop)
//    {
//
//        cout<<bucketSize<<"\t"<<numberOfBuckets<<endl;
//
//    }


    return density;
}

double NewDetector::countThresholdTheta(vector<SampleType> delta) {
    ///sort delta and get 20% first values
    sort(delta.begin(), delta.end());
    ///get 20% first samples
    int amountOfSamples = (int)(delta.size()*0.2);
    vector<SampleType> splitedDelta(delta.begin(), delta.begin()+amountOfSamples);
    ///count mean and varinace for splitedDelta

    double mean = accumulate( splitedDelta.begin(),
                              splitedDelta.end(),
                              0.0)/splitedDelta.size();
    ///variance: ((1/(n-1) * sum(i=1, n, (xi-x_sr)^2)
    double variance(0);
    for(auto& x : splitedDelta){
        variance += (x-mean)*(x-mean);
    }
    variance = variance/splitedDelta.size();
    //threshold theta
    double threshold = mean + 3*variance;

    return threshold;
}

