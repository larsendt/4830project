#include <stdio.h>
#include "OCLPerlin.h"

#include <SFML/Graphics.hpp>

#define DIM 512

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s <img dim>\n", argv[0]);
		return EXIT_FAILURE;
	}
		
	int dim = atoi(argv[1]);
	
	unsigned char* data = new unsigned char[dim * dim * 4];	
	OCLPerlin* p = new OCLPerlin();
	
	if(p->noise2D(dim, data) == EXIT_SUCCESS)
	{
		sf::Image img;
		img.LoadFromPixels(dim, dim, data);
		img.SaveToFile("/home/dane/Desktop/awesomeness.png");
		return EXIT_SUCCESS;
	}
	else
	{
		fprintf(stderr, "Perlin noise generation failed!\n");
		return EXIT_FAILURE;
	}
}
