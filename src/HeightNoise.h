#ifndef HEIGHT_NOISE_H
#define HEIGHT_NOISE_H

#include "Perlin.h"
#include "VoxelCube.h"

class HeightNoise
{
	public:
		HeightNoise();
		VoxelCube noise(int dim, int offset[3], int octaves, float frequency, float amplitude, int seed);
		
	private:
		Perlin* m_perlin;
};

#endif
