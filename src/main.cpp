#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "OCLKernel.h"

#include <CL/cl.h>

int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;
	
	OCLKernel* k = new OCLKernel("kernels/square.cl", "square");
	
	unsigned int size = 4096;
	
	float* indata = new float[size];
	float* outdata = new float[size];
	
	srand(time(NULL));
	for(unsigned int i = 0; i < size; i++)
	{
		indata[i] = (float)rand() / RAND_MAX;
	}
	
	time_t start_time = time(NULL);
	if(k->run(indata, size, outdata, size) == EXIT_SUCCESS)
	{
		printf("Kernel run finished in %d seconds.\n", time(NULL) - start_time);
	}
	else
	{
		printf("Kernel run failed!\n");
	}
	
	start_time = time(NULL);
	int errors = 0;
	for(unsigned int i = 0; i < size; i++)
	{
		float sum = 0;
		for(unsigned int j = 0; j < size; j++)
		{
			sum += indata[j];
		}
		
		if(sum != outdata[i])
		{
			errors += 1;
		}
	}
	printf("CPU run finished in %d seconds.\n", time(NULL) - start_time);
	
	if(errors == 0)
	{
		printf("Test successful! 0 errors\n");
	}
	else
	{
		printf("Test failed. %d errors\n", errors);
	}
	
	delete[] indata;
	delete[] outdata;
	delete k;
	return 0;
}
