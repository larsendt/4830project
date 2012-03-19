#include "OCLNoise.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

OCLNoise::OCLNoise()
{
	m_gradientKernel = new OCLKernel("kernels/noise.cl", "GradientNoiseArray2d");
	m_turbulenceKernel = new OCLKernel("kernels/noise.cl", "TurbulenceArray2d");
	m_monoFractalKernel = new OCLKernel("kernels/noise.cl", "MonoFractalArray2d");
	m_multiFractalKernel = new OCLKernel("kernels/noise.cl", "RidgedMultiFractalArray2d");
}

int OCLNoise::noise2D(NoiseType type, int dim, unsigned char* data)
{
	switch(type)
	{
		case GRADIENT:
			return gradientNoise2D(dim, data);
		case TURBULENCE:
			return turbulence2D(dim, data);
		case MONOFRACTAL:
			return monoFractal2D(dim, data);
		case MULTIFRACTAL:
			return multiFractal2D(dim, data);
		default:
			fprintf(stderr, "Error: Unknown noise type.\n");
			return EXIT_FAILURE;
	}
}

//----------------------------------
//            Private
//----------------------------------

int OCLNoise::gradientNoise2D(int dim, unsigned char* data)
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
	
	if(m_gradientKernel->run(4, args, 0, NULL, read_buffer_count, read_buffers, dim, dim) == EXIT_SUCCESS)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}


int OCLNoise::turbulence2D(int dim, unsigned char* data)
{
	unsigned int size = dim * dim * 4;
	unsigned char * outdata = data;
	
	float bias[2] = {128, 128};
	float scale[2] = {20, 20};
	float lacunarity = 2.02;
	float increment = 1.0;
	float octaves = 3.3;
	float amplitude = 1.0;
	
	OCLArgument args[7];
	
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
	
	a.data = &lacunarity;
	a.byte_size = sizeof(lacunarity);
	a.is_buffer = false;
	args[3] = a;
	
	a.data = &increment;
	a.byte_size = sizeof(increment);
	a.is_buffer = false;
	args[4] = a;
	
	a.data = &octaves;
	a.byte_size = sizeof(octaves);
	a.is_buffer = false;
	args[5] = a;
	
	a.data = &amplitude;
	a.byte_size = sizeof(amplitude);
	a.is_buffer = false;	
	args[6] = a;
		
	int read_buffer_count = 1;
	OCLArgument read_buffers[1];
	
	a.data = outdata;
	a.byte_size = size;
	read_buffers[0] = a;
	
	if(m_turbulenceKernel->run(7, args, 0, NULL, read_buffer_count, read_buffers, dim, dim) == EXIT_SUCCESS)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}


int OCLNoise::monoFractal2D(int dim, unsigned char* data)
{
	unsigned int size = dim * dim * 4;
	unsigned char * outdata = data;
	
	float bias[2] = {128, 128};
	float scale[2] = {20, 20};
	float lacunarity = 2.02;
	float increment = 1.0;
	float octaves = 3.3;
	float amplitude = 1.0;
	
	OCLArgument args[7];
	
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
	
	a.data = &lacunarity;
	a.byte_size = sizeof(lacunarity);
	a.is_buffer = false;
	args[3] = a;
	
	a.data = &increment;
	a.byte_size = sizeof(increment);
	a.is_buffer = false;
	args[4] = a;
	
	a.data = &octaves;
	a.byte_size = sizeof(octaves);
	a.is_buffer = false;
	args[5] = a;
	
	a.data = &amplitude;
	a.byte_size = sizeof(amplitude);
	a.is_buffer = false;	
	args[6] = a;
		
	int read_buffer_count = 1;
	OCLArgument read_buffers[1];
	
	a.data = outdata;
	a.byte_size = size;
	read_buffers[0] = a;
	
	if(m_monoFractalKernel->run(7, args, 0, NULL, read_buffer_count, read_buffers, dim, dim) == EXIT_SUCCESS)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}


int OCLNoise::multiFractal2D(int dim, unsigned char* data)
{
	unsigned int size = dim * dim * 4;
	unsigned char * outdata = data;
	
	float bias[2] = {128, 128};
	float scale[2] = {20, 20};
	float lacunarity = 2.02;
	float increment = 1.0;
	float octaves = 3.3;
	float amplitude = 1.0;
	
	OCLArgument args[7];
	
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
	
	a.data = &lacunarity;
	a.byte_size = sizeof(lacunarity);
	a.is_buffer = false;
	args[3] = a;
	
	a.data = &increment;
	a.byte_size = sizeof(increment);
	a.is_buffer = false;
	args[4] = a;
	
	a.data = &octaves;
	a.byte_size = sizeof(octaves);
	a.is_buffer = false;
	args[5] = a;
	
	a.data = &amplitude;
	a.byte_size = sizeof(amplitude);
	a.is_buffer = false;	
	args[6] = a;
		
	int read_buffer_count = 1;
	OCLArgument read_buffers[1];
	
	a.data = outdata;
	a.byte_size = size;
	read_buffers[0] = a;
	
	if(m_multiFractalKernel->run(7, args, 0, NULL, read_buffer_count, read_buffers, dim, dim) == EXIT_SUCCESS)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}












