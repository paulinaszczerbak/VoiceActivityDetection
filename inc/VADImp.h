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

class VADImp {
private:
    //int methodNumber;
public:
	VADImp();
	virtual ~VADImp();
    void detect(int methodNumber);
};

#endif /* VADIMP_H_ */
