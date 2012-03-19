#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "OCLKernel.h"

#include <CL/cl.h>
#include <SFML/Graphics.hpp>

#define DIM 1024

int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;
	
	OCLKernel* k = new OCLKernel("kernels/noise.cl", "TurbulenceArray2d");
	
	unsigned int size = DIM * DIM * 4;
	unsigned char * outdata = new unsigned char[size];
	
	for(int i = 0; i < size; i++)
	{
		outdata[i] = 255;
	}
	
	float bias[2] = {1, 1};
	float scale[2] = {1, 1};
	float lacunarity = 1;
	float increment = 1;
	float octaves = 1;
	float amplitude = 1;
	
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
	
	time_t start_time = time(NULL);
	if(k->run(7, args, 0, NULL, read_buffer_count, read_buffers) == EXIT_SUCCESS)
	{
		printf("Kernel run finished in %d seconds.\n", time(NULL) - start_time);
	}
	else
	{
		printf("Kernel run failed!\n");
	}
	
	sf::Image img;
	img.LoadFromPixels(DIM, DIM, outdata);
	img.SaveToFile("/home/dane/Desktop/awesomeness.png");
	
	delete[] outdata;
	delete k;
	return 0;
}
