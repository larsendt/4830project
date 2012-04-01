#include "OCLNoise.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

OCLNoise::OCLNoise()
{
	m_gradientKernel = new OCLKernel("kernels/noise.cl", "GradientNoiseArray2d");
	m_fbmKernel = new OCLKernel("kernels/noise.cl", "FBMNoiseArray2d");
	m_turbulenceKernel = new OCLKernel("kernels/noise.cl", "TurbulenceArray2d");
	m_monoFractalKernel = new OCLKernel("kernels/noise.cl", "MonoFractalArray2d");
	m_multiFractalKernel = new OCLKernel("kernels/noise.cl", "RidgedMultiFractalArray2d");
	m_gradient3dKernel = new OCLKernel("kernels/noise.cl", "GradientNoiseArray3d");
	m_fbm3dKernel = new OCLKernel("kernels/noise.cl", "FBMNoiseArray3d");
}

bool OCLNoise::noise2D(NoiseType type, int dim, unsigned char* data)
{
	switch(type)
	{
		case GRADIENT:
			return gradientNoise2D(dim, data);
		case FBM:
			return fbmNoise2D(dim, data);
		case TURBULENCE:
			return turbulence2D(dim, data);
		case MONOFRACTAL:
			return monoFractal2D(dim, data);
		case MULTIFRACTAL:
			return multiFractal2D(dim, data);
		default:
			fprintf(stderr, "Error: Unknown 2D noise type.\n");
			return EXIT_FAILURE;
	}
}

bool OCLNoise::noise3D(NoiseType type, int dim, unsigned char* data)
{
	switch(type)
	{
		case GRADIENT:
			return gradientNoise3D(dim, data);
		case FBM:
			return fbmNoise3D(dim, data);
		case TURBULENCE:
		case MONOFRACTAL:
		case MULTIFRACTAL:
			fprintf(stderr, "Error: Unsupported 3D noise type: %d\n", type);
			return false;
		default:
			fprintf(stderr, "Error: Unknown 3D noise type.\n");
			return false;
	}
}

//----------------------------------
//            Private
//----------------------------------

bool OCLNoise::gradientNoise3D(int dim, unsigned char* data)
{
	float bias[4] = {256, 256, 256, 256};
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
	
	if(!m_gradient3dKernel->run(5, args, 1, buffers, dim*dim*dim, 1))
	{
		fprintf(stderr, "Error: gradient 3d run failed\n");
		return false;
	}
	
	return true;
}

bool OCLNoise::fbmNoise3D(int dim, unsigned char* data)
{
	float bias[4] = {128, 128, 128, 128};
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
	
	if(!m_fbm3dKernel->run(5, args, 1, buffers, dim*dim*dim, 1))
	{
		fprintf(stderr, "Error: fbm 3d run failed\n");
		return false;
	}
	
	return true;
}

bool OCLNoise::gradientNoise2D(int dim, unsigned char* data)
{
	unsigned int size = dim * dim;// * 4;
	unsigned char * outdata = data;
	
	float bias[2] = {128, 128};
	float scale[2] = {4, 4};
	float amplitude = 1;
	
	OCLArgument args[4];
	OCLArgument buffers[1];
	
	OCLArgument a;
	a.data = outdata;
	a.byte_size = size;
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
		
	return m_gradientKernel->run(4, args, 1, buffers, dim, dim);
}


bool OCLNoise::fbmNoise2D(int dim, unsigned char* data)
{
	unsigned int size = dim * dim * 4;
	unsigned char * outdata = data;
	
	float bias[2] = {128, 128};
	float scale[2] = {4, 4};
	float amplitude = 1;
	
	OCLArgument args[4];
	OCLArgument buffers[1];
	
	OCLArgument a;
	a.data = outdata;
	a.byte_size = size;
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
	
	return m_fbmKernel->run(4, args, 1, buffers, dim, dim);
}


bool OCLNoise::turbulence2D(int dim, unsigned char* data)
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
	OCLArgument buffers[1];
	
	OCLArgument a;
	a.data = outdata;
	a.byte_size = size;
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
		
	return m_turbulenceKernel->run(7, args, 1, buffers, dim, dim);
}


bool OCLNoise::monoFractal2D(int dim, unsigned char* data)
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
	OCLArgument buffers[1];
	
	OCLArgument a;
	a.data = outdata;
	a.byte_size = size;
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
		
	return m_monoFractalKernel->run(7, args, 1, buffers, dim, dim);
}


bool OCLNoise::multiFractal2D(int dim, unsigned char* data)
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
	OCLArgument buffers[1];
	
	OCLArgument a;
	a.data = outdata;
	a.byte_size = size;
	a.is_buffer = true;
	a.buffer_index = 0;
	a.buffer_type = READ;
	buffers[0] = a;
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
		
	return m_multiFractalKernel->run(7, args, 1, buffers, dim, dim);
}

