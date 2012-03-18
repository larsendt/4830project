#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "OCLKernel.h"

int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;
	
	OCLKernel* k = new OCLKernel("kernels/square.cl", "square.cl");
	
	unsigned int insize = 4096;
	unsigned int outsize = 4096;
	
	float* indata = new float[insize];
	float* outdata = new float[outsize];
	
	srand(time(NULL));
	for(unsigned int i = 0; i < insize; i++)
	{
		indata[i] = (float)rand() / RAND_MAX;
	}
	
	k->run(indata, insize, outdata, outsize);
	
	delete[] indata;
	delete[] outdata;
	delete k;
	return 0;
}
