#ifndef CAVE_NOISE_H
#define CAVE_NOISE_H

#include "Perlin.h"
#include "VoxelCube.h"

class CaveNoise
{
	public:
		CaveNoise();
		VoxelCube noise(int dim, int offset[3], int octaves, float frequency, float amplitude, int seed, float height_cutoff);
		
	private:
		Perlin* m_perlin;
};

#endif
