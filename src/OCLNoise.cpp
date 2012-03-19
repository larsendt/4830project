#include "OCLNoise.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

OCLNoise::OCLNoise()
{
	m_kernel = new OCLKernel("kernels/noise.cl", "GradientNoiseArray2d");
}

int OCLNoise::noise2D(int dim, unsigned char* data)
{
	unsigned int size = dim * dim * 4;
	unsigned char * outdata = data;
	
	float bias[2] = {128, 128};
	float scale[2] = {20, 20};
	float amplitude = 1;
	
	OCLArgument args[4];
	
	OCLArgument a;
	a.data = outdata;
	a.byte_size = size;
	a.is_buffer = true;
	a.buffer_index = 0;
	args[0] = a;

	a.data = bias;
	a.byte_size = sizeof(bias);
	a.is_buffer = false;
	args[1] = a;
	
	a.data = scale;
	a.byte_size = sizeof(scale);
	a.is_buffer = false;
	args[2] = a;
	
	a.data = &amplitude;
	a.byte_size = sizeof(amplitude);
	a.is_buffer = false;	
	args[3] = a;
		
	int read_buffer_count = 1;
	OCLArgument read_buffers[1];
	
	a.data = outdata;
	a.byte_size = size;
	read_buffers[0] = a;
	
	time_t start_time = time(NULL);
	if(m_kernel->run(4, args, 0, NULL, read_buffer_count, read_buffers, dim, dim) == EXIT_SUCCESS)
	{
		printf("Kernel run finished in %d seconds.\n", time(NULL) - start_time);
		return EXIT_SUCCESS;
	}
	else
	{
		printf("Kernel run failed!\n");
		return EXIT_FAILURE;
	}
	
	
}
