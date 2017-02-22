/*
 * VAD.h
 *
Zawiera metody detekcji aktywności mówcy
 *
 *  Created on: 21 lip 2016
 *      Author: Paulina Szczerbak
 */

#ifndef VAD_H_
#define VAD_H_

#include <aquila/source/WaveFile.h>

class VAD {
public:
	VAD();
	virtual ~VAD();
	virtual void detect(Aquila::WaveFile wav,int methodNumber);
};

#endif /* VAD_H_ */
