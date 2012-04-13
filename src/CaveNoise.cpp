#include "CaveNoise.h"
#include <stdio.h>

CaveNoise::CaveNoise()
{

}

VoxelCube CaveNoise::noise(int dim, int offset[3], int octaves, float frequency, float amplitude, int seed, float height_cutoff)
{
	m_perlin = new Perlin(octaves, frequency, amplitude, seed);
	VoxelCube vc(dim);
	
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			for(int k = 0; k < dim; k++)
			{
				float value = m_perlin->Get3D((i+offset[0])/(float)dim,   (j+offset[1])/(float)dim, (k+offset[2])/(float)dim);
				value +=      m_perlin->Get3D((i+offset[0])/(float)dim*2, (j+offset[1])/(float)dim*2, (k+offset[2])/(float)dim*2) * 0.5;
				value +=      m_perlin->Get3D((i+offset[0])/(float)dim*4, (j+offset[1])/(float)dim*4, (k+offset[2])/(float)dim*4) * 0.5 * 0.5;
				value +=      m_perlin->Get3D((i+offset[0])/(float)dim*8, (j+offset[1])/(float)dim*8, (k+offset[2])/(float)dim*8) * 0.5 * 0.5 * 0.5;
			
				value = value * 0.5 + 0.5;
	
				if(value > 1.0)
					value = 1.0;
				else if(value < 0.0)
					value = 0.0;
				
				if(j < height_cutoff*dim)
					vc.set(i, j, k, value*255);
				else
					vc.set(i, j, k, 0);
			}
		}
	}
	
	delete m_perlin;
	return vc;
}
