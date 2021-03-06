//
// Created by paulina on 16.09.17.
//

#include <iostream>
#include <fstream>
#include "../inc/SFFDetector.h"

SFFDetector::SFFDetector(string filename) {
    _signal = new Signal(filename);
    _envelope = new Envelope(_signal->samplesCount);

}

//SFF_Combo_c6()
void SFFDetector::detect() {
    double ro(0);

    /* dodanie szumu */

    _signal->samplesNoised = addGaussNoise(_signal->samplesOriginal, 0.0001);
//    cout<<"noised "<<_signal->samplesNoised[100]<<endl;


    /* rozniczkowanie sygnalu - na zaszumionym sygnale */
    if(_envelope->differBef){
        _signal->samplesDifferential = diffSamples(_signal->samplesNoised);
    }
    else{
        _signal->samplesDifferential = _signal->samplesNoised;
    }

    /************** liczenie obwiedni *************/
    _envelope->delt = singleFrequencyFilteringEnvelope();

    cout<<"4"<<endl;

    int amountOfLoops = 20;
    if (_envelope->smoothing)
        _envelope->delt = smooth(_envelope->delt, amountOfLoops);

    cout<<"3"<<endl;

    /********* prog detekcji na delta i detekcja *********/
    _envelope->beta = countBeta();
    _envelope->beta *= _envelope->betaMult;
//    _envelope->theta = 0.5;
    _envelope->theta = countTheta();

    cout<<"2"<<endl;

    SignalSource deltaSignalSource(_envelope->delt);
    vector<short> decision = singleFrequencyFilteringDetect(deltaSignalSource);


    system("touch signal2ToPlot");
    //otwieram plik do zapisu
    ofstream file1("signal2ToPlot");
    if(file1){
        for (size_t i = 0; i<_signal->samplesNoised.size() ; i++) {
            file1 << _signal->samplesNoised[i] << endl;
        }
        file1.close();
    } else{
        cout<<"BLAD: nie mozna otworzyc pliku"<<endl;
    }

    system("touch result2ToPlot");
    //otwieram plik do zapisu
    ofstream file("result2ToPlot");
    if(file){
        for (size_t i = 0; i<decision.size() ; i++) {
            file << decision[i] << endl;
        }
        file.close();
    } else{
        cout<<"BLAD: nie mozna otworzyc pliku"<<endl;
    }

}

/// funkcja dodajaca szum do sygnalu
/// \param signal
/// \param noiseMult - mnoznik szumu
vector<Aquila::SampleType> SFFDetector::addGaussNoise(const vector<Aquila::SampleType>& signalToNoised, double noiseMult) {
    //zmienne lokalne do wygenerowania szumu
    clock_t  timer;
    //RAND_MAX - maksymalna wartosc zwrocona przez rand()
    long centr = RAND_MAX/2;
    long random1(0), random2(0);
    vector<Aquila::SampleType> samplesNoised;

    timer = clock();
    srand(timer);
    for (long i = 0; i <_signal->samplesOriginal.size() ; i++) {
        random1=0;
        for (int j = 0; j < 16 ; j++) {
            random2 = rand();
            random1 += random2 - centr;
        }
        //dodatkowe dzielenie w przypadku kompilatora 64-bitowego
        random1 /= 65536;
        random1 /= 8;
        //_signal->samplesNoised[i] = _signal->samplesOriginal[i] + noiseMult * random1;
        samplesNoised.push_back(signalToNoised[i] + noiseMult * random1);
    }
    return samplesNoised;
}


vector<Aquila::SampleType> SFFDetector::diffSamples(const vector<Aquila::SampleType>& signalToDiff) {
    vector<Aquila::SampleType> samplesDifferential;
    samplesDifferential.push_back(0);
    for (int i = 1; i <signalToDiff.size() ; i++) {
//            _signal->samplesDifferential[i] = _signal->samplesNoised[i] - _signal->samplesNoised[i-1];
        samplesDifferential.push_back(signalToDiff[i] - signalToDiff[i-1]);
    }

    return samplesDifferential;
}

//!!!!!!!!!!!!!!!!!!  tutaj zmiana squareOfEnvelope na long sprawila, ze teraz beta=0, a theta=3.95
//wczessniej  bylo theta=nan i beta miala jakas wartosc
vector<double> SFFDetector::singleFrequencyFilteringEnvelope() {
    double frequency,  mean, diff;
    int amountOfFrequencies = 185;
    vector<double> delt;
    vector<double> singleFrequencyEnvelope1;
    vector<double> singleFrequencyEnvelope2;
    vector<double> singleFrequencyEnvelope3;


    /* problem z liczeniem wariancji */
    int counter(0);
    for (int i = 0; i < amountOfFrequencies ; i+=4) {
        frequency = 300 + i*20;
        singleFrequencyEnvelope1 = singleFrequencyEnvelope(frequency);
        counter++;
        for (int j = 0; j < _signal->samplesCount ; j++) {
            //kwadrat obwiedni
            double squareOfEnvelope = singleFrequencyEnvelope1[j];
            squareOfEnvelope *= squareOfEnvelope;

            //estymata sredniej z kwadratu
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

    for (int i = 2; i < amountOfFrequencies ; i+=4) {
        frequency = 300 + i*20;
        singleFrequencyEnvelope2 = singleFrequencyEnvelope(frequency);
        counter++;
        for (int j = 0; j < _signal->samplesCount ; j++) {
            //kwadrat obwiedni
            double squareOfEnvelope = singleFrequencyEnvelope2[j];
            squareOfEnvelope *= squareOfEnvelope;

            //estymata sredniaj z kwadratu
            _envelope->factorMi[j] += squareOfEnvelope;
            mean = _envelope->factorMi[j]/counter;
            diff = squareOfEnvelope - mean;
            diff *= diff;
            _envelope->factorSigma[j] += diff;
        }
    }
    cout<<"dupa4"<<endl;

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
        double squareOfEnvelope = fabs(_envelope->factorSigma[k] * _envelope->factorSigma[k]
                                       - _envelope->factorMi[k] * _envelope->factorMi[k]);
        // _envelope->delt.push_back(pow(squareOfEnvelope, 1.0/64));
        delt.push_back(pow(squareOfEnvelope, 1.0/64));

        //_envelope->delt.push_back(1);
        //_envelope->delt[k] = pow(squareOfEnvelope, (1.0/64));
        //cout<<_envelope->delt[k]<<endl;
    }
    return delt;
}

vector<double> SFFDetector::smooth(vector<double>& signal, int loopCount) {
    vector<double> smoothedSignal = signal;
//    smoothedSignal.push_back(signal[0]);

    for (int j = 0; j < loopCount; j++) {
        for (int i = 1; i < signal.size()-1; i++) {
            smoothedSignal[i] = smoothedSignal[i-1]*0.25 + smoothedSignal[i]*0.5 + smoothedSignal[i+1]*0.25;
//            smoothedSignal.push_back(signal[i-1]*0.25 + signal[i]*0.5 + signal[i+1]*0.25);
        }
//        vector<double>::iterator iter = smoothedSignal.begin();
//        double firstVal = smoothedSignal[0];
//        double lastVal = smoothedSignal[smoothedSignal.size()-1];
//        smoothedSignal.insert(iter, firstVal);
//        smoothedSignal.push_back(lastVal);
//    signal[0] = signal[1];
//    signal[signal.size()-1]=signal[signal.size()-2];
    }


    return smoothedSignal;
}

//todo: beta value is too low!!!!!!!!!!!!!!!!
double SFFDetector::countBeta() {
    double max(0), dist(0), beta(0), maxI(0), density(0);
    vector<double> densityTab;

    /* rozklad */
    max = *max_element(_envelope->delt.begin(), _envelope->delt.end());
    densityTab = densityForPositiveValues(_envelope->delt, max);

//    for (int i = 0; i < densityTab.size(); i++) {
//        if (densityTab[i]>0)
//            cout<<densityTab[i]<<endl;
//    }

    /* wygladzenie */
    int amountOfLoops = 20;
    densityTab = smooth(densityTab, amountOfLoops);
    cout<<"density smoothed!"<<endl;

    /*maximum  lewe */
    vector<double>::iterator maxLeft = max_element(densityTab.begin()+300, densityTab.begin()+400);
    long maxLeftIndex = std::distance(densityTab.begin(), maxLeft);

    /* maximum prawe */
    vector<double>::iterator maxRight = max_element(densityTab.begin()+451,densityTab.begin()+800);
    long maxRightIndex = std::distance(densityTab.begin(), maxRight);

    /* minimum w przedziale */
    vector<double>::iterator minLocal = min_element(maxLeft,maxRight);
    long minLocalIndex = std::distance(densityTab.begin(), minLocal);

    /* wyliczenie beta dla obwiedni */
    dist = max/800;
    beta = minLocalIndex*dist;
    return beta;
}

double SFFDetector::countTheta() {
    double max(0), threshold1(0), threshold2(0), distance(0),
            mean(0), theta(0);

    vector<double> density;
    /* rozklad */
    max = *max_element(_envelope->delt.begin(), _envelope->delt.end());
    cout<<"maxxx"<<max<<endl;
    density = densityForPositiveValues(_envelope->delt, max);

    /* prog - cisza */
    threshold1 = _envelope->detectionSilenceThreshold;
    double sum(0);
    double counter(0);
    for (int i = 0; i < 801 ; i++) {
        sum += density[i];
//        cout<<"density"<<density.size()<<endl;
        if (sum > threshold1) {
            counter = i;
            break;
        }
    }
//    cout<<"counter"<<counter<<endl;
    distance = max/800;
    threshold2 = counter * distance + distance/2;

    /* srednia dla "ciszy" */
    sum =0;
    counter = 0;
    for (int j = 0; j < _envelope->delt.size() ; j++) {
        if (_envelope->delt[j]<threshold2){
            sum += _envelope->delt[j];
            counter++;
        }
    }
    if (counter > 0)
        mean = sum/counter;
    else
        mean = 0.1 * distance;

    /* odchylenie standardowe dla "ciszy" */
    sum = 0;
    counter = 0;
    for (int k = 0; k < _signal->samplesCount ; k++) {
        sum += (_envelope->delt[k] - mean)*(_envelope->delt[k] - mean);
        counter++;
    }

    double factor(0);
    if (counter > 0)
        factor = sum/counter;
    else
        factor = 0.1 * distance;
    factor = sqrt(factor);
    theta = mean + 3*factor;

    return theta;
}

vector<short> SFFDetector::singleFrequencyFilteringDetect(const SignalSource& signalToDetect) {
    vector<short> decision;
    double beta(0), theta(0);
    bool isSilence = true;

    beta = _envelope->beta;
    theta = _envelope->theta;
    cout<<"beta:"<<_envelope->beta<<endl;
    cout<<"theta:"<<_envelope->theta<<endl;

    double frameLengthInSecs = 0.1;
    double frameStepInSecs = 0.3;
    unsigned int samplesPerFrame =  (unsigned int)(_signal->samplingFrequency * frameLengthInSecs);
    unsigned int frameStep = (unsigned int)(_signal->samplingFrequency*frameStepInSecs);
    unsigned int samplesPerOverlap = samplesPerFrame - frameStep;

    FramesCollection frames(signalToDetect, samplesPerFrame);
//    FramesCollection frames;
//    frames.createFromDuration(signalToDetect, frameLengthInSecs);

    cout<<"frames amount "<<frames.count()<<endl;
    for(FramesCollection::iterator frame = frames.begin();
        frame!=frames.end();
        frame++){
        int speechCounter(0);
        double percentage(0);
        for (SignalSource::iterator sample = (*frame).begin();
             sample!=(*frame).end();
             sample++) {
            if((*sample)>beta){
                speechCounter++;
            }
        }
        percentage = 1.0 * speechCounter / samplesPerFrame;
        cout<<"percentage"<<percentage<<endl;

        if (percentage > _envelope->percent){
            for (int i = 0; i < samplesPerFrame; i++) {
                decision.push_back(1);
            }
        }else{
            for (int i = 0; i < samplesPerFrame; i++) {
                decision.push_back(0);
            }
        }
    }
    cout<<"sampl freq "<<_signal->samplingFrequency<<endl;
    cout<<"decision size "<<decision.size()<<endl;
    return decision;
}

///funkcja do obliczania gestosci dla pozytywnych wartosci
/// oblicza wspolczynnik normowania
/// usunieto czesc argumentow - zostaly przerzucine do klasy jako zmienne prywatne
/// \param sPosNb - liczba punktow w rozkladzie prawdopodobienstwa, przyjete tak, bo tak jest ok
/// \param max
vector<double> SFFDetector::densityForPositiveValues(vector<double> VAETab, double max
        /*double* VAEDensity, short sPosNb*/ ) {
    double normFactor;
    long temp;
    vector<double> result(VAETab.size(),0);


    /************** wspolczynnik normowania *************/
    normFactor = (sPosNb-1)/max;

    for (int i = 0; i < VAETab.size(); i++) {
        temp = (long) floor(normFactor*VAETab[i]+0.5);
        //cout<<"temp "<<temp<<endl;
        if (temp <= sPosNb && temp > 0){
//            cout<<temp<<endl;
            result[temp] = result[temp]+1;
        }
    }
    for (int j = 0; j < sPosNb ; j++) {
        result[j] /= sPosNb;
    }

    return result;
}

/// funckcja do obliczania czestotliwosci obwiedni
/// \param frequency - czestotliwosc
vector<double> SFFDetector::singleFrequencyEnvelope(double frequency) {

    double filterFactorCos(0), filterFactorSin(0);
    double normalizedFrequency(0), max(0), threshold1(0),
            threshold2(0), sum(0), distance(0), module(0);

    vector<double> singleFrequencyEnvelope;

    //wzor na omegak z artykulu
    normalizedFrequency = 2*PI*frequency/_signal->samplingFrequency;
    module = _envelope->singlePoleModule;

    //wspolczynniki filtru kwadraturowego
    filterFactorCos = module * cos(normalizedFrequency);
    filterFactorSin = module * sin(normalizedFrequency);

    /*rekursywna filtracja kwadraturowa*/
    for (int i = 1; i < _signal->samplesCount ; i++) {
        _envelope->factorXr[i] = _signal->samplesDifferential[i] + filterFactorCos * _envelope->factorXr[i-1] - filterFactorSin * _envelope->factorXi[i-1];
        _envelope->factorXi[i] = filterFactorCos * _envelope->factorXi[i-1] + filterFactorSin * _envelope->factorXr[i-1];
        //cout<<_envelope->factorXi[i]<<endl;
    }

    /* obwednia - wzor z artykulu*/
    if (_envelope->singleFrequencyEnvelope.size() == 0){
        for (int j = 0; j < _signal->samplesCount ; j++) {
            _envelope->singleFrequencyEnvelope.push_back(_envelope->factorXr[j]*_envelope->factorXr[j] - _envelope->factorXi[j] * _envelope->factorXi[j]);
            //cout<<_envelope->singleFrequencyEnvelope[j]<<endl;
        }
    } else{
        for (int j = 0; j < _envelope->singleFrequencyEnvelope.size() ; j++) {
            _envelope->singleFrequencyEnvelope[j] = _envelope->factorXr[j]*_envelope->factorXr[j] - _envelope->factorXi[j] * _envelope->factorXi[j];
            //cout<<_envelope->singleFrequencyEnvelope[j]<<endl;
        }
    }

    for (int j = 0; j < _signal->samplesCount ; j++) {
        singleFrequencyEnvelope.push_back(_envelope->factorXr[j]*_envelope->factorXr[j] - _envelope->factorXi[j] * _envelope->factorXi[j]);
        //cout<<_envelope->singleFrequencyEnvelope[j]<<endl;
    }


    /* dystrybuanta */
    max = *max_element(singleFrequencyEnvelope.begin(), singleFrequencyEnvelope.end());
    //cout<<"max: "<<max<<endl;
    _envelope->density = densityForPositiveValues(singleFrequencyEnvelope, max);
    //cout<<density[100]<<endl;
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
    for (int k = 0; k < singleFrequencyEnvelope.size() ; k++) {
        if(singleFrequencyEnvelope[k] < threshold2){
            sum += singleFrequencyEnvelope[k];
            counter++;
        }
    }
    if (counter > 0)
        sum /= counter;
    else
        sum = 0.1 * distance;

    /* skalownaie obwiedni */
    sum *= 32768;
    for (int i = 0; i < singleFrequencyEnvelope.size() ; i++)
        singleFrequencyEnvelope[i] = singleFrequencyEnvelope[i]/sum;

    return singleFrequencyEnvelope;
}



//oblicza energie dla pojedynczej ramki
double SFFDetector::countEnergy(Aquila::FramesCollection* frames, Aquila::SampleType frameIndex) {
    double energy(0);
    //iteruje po probkach w ramce
    for (size_t i = 0; i < frames->getSamplesPerFrame() ; i++) {
        energy += frames->frame(frameIndex).sample(i)*frames->frame(frameIndex).sample(i);
    }
    return energy;
}





