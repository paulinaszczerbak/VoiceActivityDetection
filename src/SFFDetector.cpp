//
// Created by paulina on 07.07.17.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>

#include "../inc/SFFDetector.h"

SFFDetector::SFFDetector(std::string filename) {
    _signal = new Signal(filename);
    _envelope = new Envelope(_signal->samplesCount);

}

SFFDetector::Signal::Signal(std::string filename) {
    signalOriginal = new Aquila::WaveFile(filename);
    samplesCount = signalOriginal->getSamplesCount();
    //samplesOriginal = new Aquila::SampleType[samplesCount];
    samplesOriginal = (Aquila::SampleType *) malloc(samplesCount * sizeof(Aquila::SampleType));
    samplesNoised = new Aquila::SampleType[samplesCount];
    samplesDifferential = new Aquila::SampleType[samplesCount];
    samplingFrequency = signalOriginal->getSampleFrequency();

    std::copy(signalOriginal->toArray(),
              signalOriginal->toArray()+samplesCount,
              samplesOriginal);
    //czy moze lepiej mamset?
    std::memset(samplesNoised, 0, samplesCount*sizeof(Aquila::SampleType));
//    std::copy(signalOriginal->toArray(),
//              signalOriginal->toArray()+samplesCount,
//              samplesNoised);
    std::memset(samplesDifferential, 0, samplesCount*sizeof(Aquila::SampleType));
//    std::copy(signalOriginal->toArray(),
//              signalOriginal->toArray()+samplesCount,
//              samplesDifferential);
}

SFFDetector::Signal::~Signal() {
    delete signalOriginal;
    delete samplesOriginal;
    delete samplesNoised;
    delete samplesDifferential;
}

SFFDetector::Envelope::Envelope(int samplesCount) {
    this->samplesCount=samplesCount;
    this->singleFrequencyEnvelope = (double *) malloc(samplesCount * sizeof(double));
    this->singlePoleModule=0.97;
//    this->firstThreshold=0.15;
    this->differBef = true;
    this->smoothing = true;

    factorXi = (double *) malloc(samplesCount * sizeof(double));
    factorXr = (double *) malloc(samplesCount * sizeof(double));
    density = (double *) malloc(sPosNb * sizeof(double));
    factorMi = (double *) malloc(samplesCount * sizeof(double));
    factorSigma = (double *) malloc(samplesCount * sizeof(double));
    delt = (double *) malloc(samplesCount * sizeof(double));


    memset(singleFrequencyEnvelope, 0, samplesCount );
    memset(factorXi,0, samplesCount );
    memset(factorXr,0, samplesCount );
    memset(density, 0, sPosNb*sizeof(double));
    memset(factorMi, 0, samplesCount*sizeof(double));
    memset(factorSigma, 0, samplesCount*sizeof(double));
    memset(delt, 0, samplesCount*sizeof(double));
}

SFFDetector::Envelope::~Envelope() {
    delete singleFrequencyEnvelope;
    delete factorXi;
    delete factorXr;
    delete density;
    delete factorMi;
    delete factorSigma;
    delete delt;
}

void SFFDetector::printSamples() {

    addGaussNoise(0.0001);

    if(_envelope->differBef){
        for (int i = 1; i <_signal->samplesCount ; i++) {
            _signal->samplesDifferential[i] = _signal->samplesNoised[i] - _signal->samplesNoised[i-1];

        }
    }
    else{
        for (int i = 0; i < _signal->samplesCount ; i++) {
            _signal->samplesDifferential[i] = _signal->samplesNoised[i];
        }
    }

    singleFrequencyEnvelope(4000);

    system("touch result2ToPlot");
    //otwieram plik do zapisu
    std::ofstream file("result2ToPlot");
    int xValue(0);
    int arraySize = sizeof(_envelope->singleFrequencyEnvelope)/sizeof(_envelope->singleFrequencyEnvelope[0]);
    if(file){
        for (size_t i = 0; i < _signal->samplesCount ; i++) {
            file << _envelope->singleFrequencyEnvelope[i] << std::endl;
        }
        file.close();
    } else{
        std::cout<<"BLAD: nie mozna otworzyc pliku"<<std::endl;
    }

    //findMaxValue(_envelope->singleFrequencyEnvelope);
}

/// funkcja dodajaca szum do sygnalu
/// \param signal
/// \param noiseMult - mnoznik szumu
void SFFDetector::addGaussNoise(double noiseMult) {
    //zmienne lokalne do wygenerowania szumu
    clock_t  timer;
    //RAND_MAX - maksymalna wartosc zwrocona przez rand()
    long centr = RAND_MAX/2;
    long random1(0), random2(0);

    timer = clock();
    srand(timer);
    for (long i = 0; i <_signal->samplesCount ; i++) {
        random1=0;
        for (int j = 0; j < 16 ; j++) {
            random2 = rand();
            random1 += random2 - centr;
        }
        //dodatkowe dzielenie w przypadku kompilatora 64-bitowego
        random1 /= 65536;
        random1 /= 8;
        _signal->samplesNoised[i] = _signal->samplesOriginal[i] + noiseMult * random1;
    }
}

///funkcja do obliczania gestosci dla pozytywnych wartosci
/// oblicza wspolczynnik normowania
/// usunieto czesc argumentow - zostaly przerzucine do klasy jako zmienne prywatne
/// \param sPosNb
/// \param max
void SFFDetector::densityForPositiveValues(double* VAETab, double max
                                           /*double* VAEDensity, short sPosNb*/ ) {
    double normFactor;
    short temp;

    normFactor = (sPosNb-1)/max;

    //memset(VAEDensity, 0, sPosNb*sizeof(double));

    for (int i = 0; i < sizeof(VAETab) ; i++) {
        temp = (long) floor(normFactor*VAETab[i]+0.5);
        if (temp <= sPosNb){
             _envelope->density[temp]++;
        }
    }
    for (int j = 0; j < sPosNb ; j++) {
        _envelope->density[j] /= _signal->samplesCount;
    }
}

/// funckcja do obliczania czestotliwosci obwiedni
/// \param frequency - czestotliwosc
void SFFDetector::singleFrequencyEnvelope(double frequency) {

    double filterFactorCos(0), filterFactorSin(0);
    double normalizedFrequency(0), max(0), threshold1(0),
            threshold2(0), sum(0), distance(0), module(0);
    long sigLength(0);

    sigLength=_signal->samplesCount;

    //wzor na omegak z artykulu
    normalizedFrequency = 2*PI*frequency/_signal->samplingFrequency;
    module = _envelope->singlePoleModule;

    //wspolczynniki filtru kwadraturowego
    filterFactorCos = module * cos(normalizedFrequency);
    filterFactorSin = module * sin(normalizedFrequency);

    /*rekursywna filtracja kwadraturowa*/
    for (int i = 1; i < sigLength ; i++) {
        _envelope->factorXr[i] = _signal->samplesDifferential[i] + filterFactorCos * _envelope->factorXr[i-1] - filterFactorSin * _envelope->factorXi[i-1];
        _envelope->factorXi[i] = filterFactorCos * _envelope->factorXi[i-1] + filterFactorSin * _envelope->factorXr[i-1];
    }

    /* obwednia - wzor z artykulu*/
    for (int j = 0; j < sigLength ; j++) {
        _envelope->singleFrequencyEnvelope[j] = sqrt(_envelope->factorXr[j]*_envelope->factorXr[j] - _envelope->factorXi[j] * _envelope->factorXi[j]);
    }

    /* dystrybuanta */
    max = findMaxValue(_envelope->singleFrequencyEnvelope);
    densityForPositiveValues(_envelope->singleFrequencyEnvelope, max);

    /* prog - cisza */
    threshold1 = _envelope->initialThreshold;
    int maxK(0);
    for (int k = 0; k < sPosNb ; k++) {
        sum += _envelope->density[k];
        if (sum > threshold1)
            break;
        else maxK = k;
    }
    distance = max / 800;
    threshold2 = maxK * distance + distance / 2;

    /* srednia dla "ciszy" */
    sum = 0;
    int counter(0);
    for (int k = 0; k < _signal->samplesCount ; k++) {
        if(_envelope->singleFrequencyEnvelope[k] < threshold2){
            sum += _envelope->singleFrequencyEnvelope[k];
            counter++;
        }
    }
    if (counter > 0)
        sum /= counter;
    else
        sum = 0.1 * distance;

    /* skalownaie obwiedni */
    sum *= 32768;
    for (int i = 0; i < sizeof(_envelope->singleFrequencyEnvelope) ; i++)
        _envelope->singleFrequencyEnvelope[i] = _envelope->singleFrequencyEnvelope[i]/sum;

}

double SFFDetector::findMaxValue(double *array) {
    //double max = *std::max_element(array, array + sizeof(array));
    return *std::max_element(array, array + sizeof(array));
}

double SFFDetector::findMaxAbsValue(double *array) {
    double* absArray;
    for (int i = 0; i < sizeof(array) ; i++) {
        absArray[i]=fabs(array[i]);
    }
    return findMaxValue(absArray);
}

void SFFDetector::detect() {
    double ro(0);

    /* dodanie szumu */
    addGaussNoise(0.0001);

    /* rozniczkowanie sygnalu - na zaszumionym sygnale */
    if(_envelope->differBef){
        for (int i = 1; i <_signal->samplesCount ; i++) {
            _signal->samplesDifferential[i] = _signal->samplesNoised[i] - _signal->samplesNoised[i-1];

        }
    }
    else{
        for (int i = 0; i < _signal->samplesCount ; i++) {
            _signal->samplesDifferential[i] = _signal->samplesNoised[i];
        }
    }

    //todo:
    /* liczenie obwiedni */

    singleFrequencyFilteringEnvelope();
    if (_envelope->smoothing)
  //      makeSmooth(_envelope->delt, _envelope.smoothingRank);

    /* prog detekcji na delta i detekcja */
//    _envelope.beta = singleFrequencyFilteringBeta();
//    _envelope.beta *= _envelope.betaMult;
//    _envelope.theta = singleFrequencyFilteringTheta();
//
//    ro = singleFrequencyFilteringRoCalc();
//    singleFrequencyFilteringDetect();

    system("touch result2ToPlot");
    //otwieram plik do zapisu
    std::ofstream file("result2ToPlot");
    int xValue(0);
    int arraySize = sizeof(_envelope->singleFrequencyEnvelope)/sizeof(_envelope->singleFrequencyEnvelope[0]);
    if(file){
        for (size_t i = 0; i < _signal->samplesCount ; i++) {
            file << _envelope->singleFrequencyEnvelope[i] << std::endl;
        }
        file.close();
    } else{
        std::cout<<"BLAD: nie mozna otworzyc pliku"<<std::endl;
    }

}

void SFFDetector::singleFrequencyFilteringEnvelope() {
    double frequency, squareOfEnvelope, mean, diff;

    /* problem z liczeniem wariancji */
    int counter(0);
    for (int i = 0; i < 186 ; i+=4) {
        frequency = 300 + i*20;
        singleFrequencyEnvelope(frequency);
        counter++;
        for (int j = 0; j < _signal->samplesCount ; j++) {
            //kwadrat obwiedni
            squareOfEnvelope = _envelope->singleFrequencyEnvelope[j];
            squareOfEnvelope *= squareOfEnvelope;

            //estymata sredniaj z kwadratu
            _envelope->factorMi[j] += squareOfEnvelope;
            mean = _envelope->factorMi[j]/counter;
            diff = squareOfEnvelope - mean;
            diff *= diff;
            _envelope->factorSigma[j] += diff;
        }
    }

//    for (int i = 1; i < 186 ; i+=4) {
//        frequency = 300 + i*20;
//        singleFrequencyEnvelope(frequency);
//        counter++;
//        for (int j = 0; j < _signal->samplesCount ; j++) {
//            //kwadrat obwiedni
//            squareOfEnvelope = _envelope->singleFrequencyEnvelope[j];
//            squareOfEnvelope *= squareOfEnvelope;
//
//            //estymata sredniaj z kwadratu
//            _envelope->factorMi[j] += squareOfEnvelope;
//            mean = _envelope->factorMi[j]/counter;
//            diff = squareOfEnvelope - mean;
//            diff *= diff;
//            _envelope->factorSigma[j] += diff;
//        }
//    }

    for (int i = 2; i < 186 ; i+=4) {
        frequency = 300 + i*20;
        singleFrequencyEnvelope(frequency);
        counter++;
        for (int j = 0; j < _signal->samplesCount ; j++) {
            //kwadrat obwiedni
            squareOfEnvelope = _envelope->singleFrequencyEnvelope[j];
            squareOfEnvelope *= squareOfEnvelope;

            //estymata sredniaj z kwadratu
            _envelope->factorMi[j] += squareOfEnvelope;
            mean = _envelope->factorMi[j]/counter;
            diff = squareOfEnvelope - mean;
            diff *= diff;
            _envelope->factorSigma[j] += diff;
        }
    }

//    for (int i = 3; i < 186 ; i+=4) {
//        frequency = 300 + i*20;
//        singleFrequencyEnvelope(frequency);
//        counter++;
//        for (int j = 0; j < _signal->samplesCount ; j++) {
//            //kwadrat obwiedni
//            squareOfEnvelope = _envelope->singleFrequencyEnvelope[j];
//            squareOfEnvelope *= squareOfEnvelope;
//
//            //estymata sredniaj z kwadratu
//            _envelope->factorMi[j] += squareOfEnvelope;
//            mean = _envelope->factorMi[j]/counter;
//            diff = squareOfEnvelope - mean;
//            diff *= diff;
//            _envelope->factorSigma[j] += diff;
//        }
//    }

    /* normowanie */
    for (int k = 0; k < _signal->samplesCount ; k++) {
        _envelope->factorMi[k] /= counter;
        _envelope->factorSigma[k] /= counter;
        _envelope->factorSigma[k] = sqrt(_envelope->factorSigma[k]);
    }

    /* miara */
    for (int k = 0; k < _signal->samplesCount ; k++) {
        squareOfEnvelope = fabs(_envelope->factorSigma[k] * _envelope->factorSigma[k]
                                - _envelope->factorMi[k] * _envelope->factorMi[k]);
        _envelope->delt[k] = pow(squareOfEnvelope, 1.0/64);
    }
}

double SFFDetector::singleFrequencyFilteringBeta() {
    double max(0), threshold1(0), threshold2(0), temp(0), distance(0),
            mean(0), std(0), spMean(0), beta(0);

    /* rozklad */
    max = findMaxValue(_envelope->delt);
    densityForPositiveValues(_envelope->delt, max);

    /* prog - cisza */

    return 0;
}



