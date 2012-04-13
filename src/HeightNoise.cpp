#include "HeightNoise.h"
#include <stdio.h>

HeightNoise::HeightNoise()
{
}

VoxelCube HeightNoise::noise(int dim, int offset[3], int octaves, float frequency, float amplitude, int seed)
{
	VoxelCube vc(dim);
	m_perlin = new Perlin(octaves, frequency, amplitude, seed);
	
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			float value = m_perlin->Get((i+offset[0])/(float)dim, (j+offset[2])/(float)dim);
			value +=      m_perlin->Get((i+offset[0])/(float)dim*2, (j+offset[2])/(float)dim*2) * 0.5;
			value +=      m_perlin->Get((i+offset[0])/(float)dim*4, (j+offset[2])/(float)dim*4) * 0.5 * 0.5;
			value +=      m_perlin->Get((i+offset[0])/(float)dim*8, (j+offset[2])/(float)dim*8) * 0.5 * 0.5 * 0.5;
			
			value = value * 0.5 + 0.5;
			
			if(value > 1.0)
				value = 1.0;
			else if(value < 0.0)
				value = 0.0;
			
			for(int k = 0; k < dim*value; k++)
			{
				vc.set(i, k, j, 255);
			}
			
			for(int k = dim*value; k < dim; k++)
			{
				vc.set(i, k, j, 0);
			}
		}
	}
	
	return vc;
}
