#include "OCL3DFBMNoise.h"
#include <stdio.h>

OCL3DFBMNoise::OCL3DFBMNoise()
{
	m_kernel = new OCLKernel("kernels/fbmnoise.cl", "FBMNoiseArray3d");
}

bool OCL3DFBMNoise::noise(int dim, unsigned char* data, float pos[3])
{
	float bias[4] = {pos[0],pos[1],pos[2], 256};
	float scale[4] = {2, 2, 2, 2};
	float amplitude = 1;

	OCLArgument args[5];
	OCLArgument buffers[1];

	OCLArgument a;
	a.data = data;
	a.byte_size = dim * dim * dim * sizeof(unsigned char);
	a.is_buffer = true;
	a.buffer_index = 0;
	a.buffer_type = READ;
	args[0] = a;
	buffers[0] = a;

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
	
	a.data = &dim;
	a.byte_size = sizeof(dim);
	a.is_buffer = false;
	args[4] = a;
	
	if(!m_kernel->run(5, args, 1, buffers, dim*dim*dim, 1))
	{
		fprintf(stderr, "Error: fbm 3d run failed\n");
		return false;
	}
	
	return true;
}
