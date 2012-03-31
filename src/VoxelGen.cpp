#include "VoxelGen.h"
#include <stdio.h>

VoxelGen::VoxelGen()
{
	m_voxels = NULL;
}

VoxelGen::~VoxelGen()
{
	if(m_voxels)
	{
		for(int i = 0; i < m_voxelCount; i++)
		{	
			delete m_voxels[i].pos;
		}
	
		delete[] m_voxels;
	}
}

void VoxelGen::set3DNoiseData(unsigned char* data, int dim, float spacing)
{
	int index = 0;
	m_voxels = new VOXEL[dim*dim*dim];
	m_voxelCount = 0;
	
	VOXEL v;
	COORD3D* pos;

	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			for(int k = 0; k < dim; k++)
			{
				if(data[index] > 128)
				{
					pos = new COORD3D;
					pos->a = i*spacing;
					pos->b = j*spacing;
					pos->c = k*spacing;
					v.pos = pos;
					m_voxels[m_voxelCount] = v;
					m_voxelCount += 1;
				}
				index += 1;
			}
		}
	}
}
