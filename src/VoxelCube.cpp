#include "VoxelCube.h"
#include <stdio.h>

VoxelCube::VoxelCube(int dim)
{
	m_dim = dim;
	m_data = new unsigned char[dim*dim*dim];
}	

VoxelCube::~VoxelCube()
{
	//delete[] m_data;
}

unsigned char VoxelCube::at(int x, int y, int z)
{
	return m_data[index1d(x, y, z)];
}

void VoxelCube::set(int x, int y, int z, unsigned char value)
{
	m_data[index1d(x, y, z)] = value;
}

int VoxelCube::index1d(int x, int y, int z)
{
	int id = (x*m_dim*m_dim) + (y*m_dim) + z;
	if(id > m_dim*m_dim*m_dim)
	{
		fprintf(stderr, "VoxelCube bad index (%d) for x=%d y=%d z=%d, max=%d\n", id, x, y, z, m_dim);
		id = 0;
	}
	return id;
}

void VoxelCube::decompose1dIndex(int index, int* x, int* y, int* z)
{
	*x = index/(m_dim*m_dim);
	*y = (index - (*x*m_dim*m_dim)) / m_dim;
	*z = index - (*x*m_dim*m_dim) - (*y*m_dim);
}

VoxelCube& VoxelCube::operator-(VoxelCube other)
{
	if(other.dimension() != dimension())
	{
		fprintf(stderr, "VoxelCube operator-() dimensions do not match (%d != %d)\n", other.dimension(), dimension());
		return *this;
	}
	
	VoxelCube result = *this;
	for(int i = 0; i < m_dim; i++)
	{
		for(int j = 0; j < m_dim; j++)
		{
			for(int k = 0; k < m_dim; k++)
			{
				//unsigned char diff = 0;
				///if(at(i, j, k) > other.at(i, j, k))
					//diff = at(i, j, k) - other.at(i, j, k);
				
				if(other.at(i, j, k) > 128)
					result.set(i, j, k, 0);
			}
		}
	}
	
	return result;
};

VoxelCube& VoxelCube::operator+(VoxelCube other)
{
	if(other.dimension() != dimension())
	{
		fprintf(stderr, "VoxelCube operator+() dimensions do not match (%d != %d)\n", other.dimension(), dimension());
		return *this;
	}
	
	VoxelCube result(m_dim);
	for(int i = 0; i < m_dim; i++)
	{
		for(int j = 0; j < m_dim; j++)
		{
			for(int k = 0; k < m_dim; k++)
			{
				unsigned char add = 255;
				if(at(i, j, k) + other.at(i, j, k) < 255)
					add = at(i, j, k) + other.at(i, j, k);
					
				result.set(i, j, k, add);
			}
		}
	}
	
	return result;
};

// sets all of the bottom voxels to 255
void VoxelCube::addFloor()
{
	for(int x = 0; x < m_dim; x++)
	{
		for(int z = 0; z < m_dim; z++)
		{
			set(x, 0, z, 255);
		}
	}
}

void VoxelCube::fillBoundaries(bool xneg_bound, bool xpos_bound, bool yneg_bound, bool ypos_bound, bool zneg_bound, bool zpos_bound)
{
	for(int x = 0; x < m_dim; x++)
	{
		for(int y = 0; y < m_dim; y++)
		{
			for(int z = 0; z < m_dim; z++)
			{
				if(at(x, y, z) > 128)
				{
					if(xneg_bound && x == 0)
						set(x, y, z, 0);
						
					if(xpos_bound && x >= m_dim-1)
						set(x, y, z, 0);
						
					if(yneg_bound && y == 0)
						set(x, y, z, 0);
						
					if(ypos_bound && y >= m_dim-1)
						set(x, y, z, 0);
						
					if(zneg_bound && z == 0)
						set(x, y, z, 0);
						
					if(zpos_bound && z >= m_dim-1)
						set(x, y, z, 0);
				}
			}
		}
	}
}

