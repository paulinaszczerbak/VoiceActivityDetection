/*
 * WAVReaderImp.cpp
 *
 *  Created on: 8 lip 2016
 *      Author: paula
 */

#include "../inc/WAVReaderImp.h"

WAVReaderImp::WAVReaderImp() {
	// TODO Auto-generated constructor stub

}

WAVReaderImp::~WAVReaderImp() {
	// TODO Auto-generated destructor stub
}




void WAVReaderImp::readFile() {

	FILE * infile = fopen("../kabanos.wav","rb");		// Open wave file in read mode
	FILE * outfile = fopen("Output.wav","wb");		// Create output ( wave format) file in write mode

	int BUFSIZE = 512;					// BUFSIZE can be changed according to the frame size required (eg:512)
	int count = 0;						// For counting number of frames in wave file.
	short int buff16[BUFSIZE];				// short int used for 16 bit as input data format is 16 bit PCM audio
	header_p meta = (header_p)malloc(sizeof(header));	// header_p points to a header struct that contains the wave file metadata fields
	int nb;							// variable storing number of byes returned
	if (infile)
	{
		fread(meta, 1, sizeof(header), infile);
		fwrite(meta,1, sizeof(*meta), outfile);
		cout << " Size of Header file is "<<sizeof(*meta)<<" bytes" << endl;
		cout << " Sampling rate of the input wave file is "<< meta->sample_rate <<" Hz" << endl;
		cout << " Number of samples in wave file are " << meta->subchunk2_size << " samples" << endl;



		while (!feof(infile))
		{
			nb = fread(buff16,1,BUFSIZE,infile);		// Reading data in chunks of BUFSIZE
			//cout << nb <<endl;
			count++;					// Incrementing Number of frames

			/* Insert your processing code here*/

			fwrite(buff16,1,nb,outfile);			// Writing read data into output file
		}
	cout << " Number of frames in the input wave file are " <<count << endl;
	}

}
