/*
 * WAVReaderImp.h
 *
 *  Created on: 8 lip 2016
 *      Author: Paulina Szczerbak
 */

/**
 * Klasa sluzaca do wczytywania plikow z rozszerzeniem WAV.
 * Dzieli sygnal na ramki i zlicza ich ilosc.
 */
/*wav_read_write.cpp
Author: K. L. Srinivas
Problem statement :
1. opens a wav file for reading; opens another wav file for writing
2. detects the samp. rate and #samples from the header of input wav

Next, we wish to read in sequentially blocks of data from the wav file
for processing one block ("frame") at a time.

In the loop (until last frame):
 3. reads in the data (16-bit integers) in blocks of BUFSIZE samples
 4. dummy processing()
 5. writes out BUFSIZE output samples in the output wav file
end loop
*/

// This program is tested on linux machine with g++ compiler.


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#ifndef WAVREADERIMP_H_
#define WAVREADERIMP_H_
using namespace std;

class WAVReaderImp {
private:
	// WAVE PCM soundfile format (you can find more in https://ccrma.stanford.edu/courses/422/projects/WaveFormat/ )
	typedef struct header_file
	{
	    char chunk_id[4];
	    int chunk_size;
	    char format[4];
	    char subchunk1_id[4];
	    int subchunk1_size;
	    short int audio_format;
	    short int num_channels;
	    int sample_rate;			// sample_rate denotes the sampling rate.
	    int byte_rate;
	    short int block_align;
	    short int bits_per_sample;
	    char subchunk2_id[4];
	    int subchunk2_size;			// subchunk2_size denotes the number of samples.
	} header;

	typedef struct header_file* header_p;

public:
	WAVReaderImp();
	virtual ~WAVReaderImp();
	void readFile();

};

#endif /* WAVREADERIMP_H_ */
