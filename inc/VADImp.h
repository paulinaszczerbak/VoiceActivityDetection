/*
 * VADImp.h
 *
 *  Created on: 21 lip 2016
 *      Author: paula
 *
 *      klasa do wybierania metody detekcji
 */

#ifndef VADIMP_H_
#define VADIMP_H_

//#include "WAVFileSetterImp.h"

#include <aquila/source/WaveFile.h>
#include "VAD.h"
//#include "EnergyBasedDetector.h"

class VADImp : public VAD {
private:
    //int methodNumber;
    double frameLength;
public:
	VADImp();
	virtual ~VADImp();
    void detect(Aquila::WaveFile wav,int methodNumber);
    double getFrameLengthInSECs();
};

#endif /* VADIMP_H_ */
