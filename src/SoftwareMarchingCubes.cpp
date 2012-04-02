#include "SoftwareMarchingCubes.h"
#include <stdio.h>
#include <string.h>

#include "MCLookupTable.h"


SoftwareMarchingCubes::SoftwareMarchingCubes()
{
	m_vbo = new VertexBufferObject(GL_TRIANGLES);
}

SoftwareMarchingCubes::~SoftwareMarchingCubes()
{
	delete m_vbo;
}

void SoftwareMarchingCubes::setNoiseData(unsigned char* noise, int dim, float spacing)
{
	m_dim = dim;
	// maximum possible is dim*dim*dim voxels times a maximum of 12 vertices per voxel
	// TODO: we'll never hit this limit, so set things up to use a smaller inital amount and expand if necessary
	int max_vxs = dim*dim*dim*12;
	VERTEX* vertices = new VERTEX[max_vxs];
	GLuint* indices = new GLuint[max_vxs];
	int vx_count = 0;
	
	for(int x = 0; x < dim-1; x++)
	{
		for(int y = 0; y < dim-1; y++)
		{
			for(int z = 0; z < dim-1; z++)
			{
				unsigned int i0 = index1D(x, y, z);
				unsigned int i1 = index1D(x+1, y, z);
				unsigned int i2 = index1D(x, y+1, z);
				unsigned int i3 = index1D(x, y, z+1);
				unsigned int i4 = index1D(x+1, y+1, z);
				unsigned int i5 = index1D(x, y+1, z+1);
				unsigned int i6 = index1D(x+1, y, z+1);
				unsigned int i7 = index1D(x+1, y+1, z+1);
				
				unsigned char accum = 0x0;
				
				accum |= (noise[i0] >= 128) << 0;
				accum |= (noise[i1] >= 128) << 1;
				accum |= (noise[i2] >= 128) << 2;
				accum |= (noise[i3] >= 128) << 3;
				accum |= (noise[i4] >= 128) << 4;
				accum |= (noise[i5] >= 128) << 5;
				accum |= (noise[i6] >= 128) << 6;
				accum |= (noise[i7] >= 128) << 7;
				
				if(accum != 0xff && accum != 0x0)
				{
					char* ids = MCIndices[accum];
					int idcount = strlen(ids);
					
					for(int i = 0; i < idcount; i++)
					{
						COORD3D* c = new COORD3D;
						c->a = (x*spacing) + (MCGetVertex(ids[i])[0] * spacing);
						c->b = (y*spacing) + (MCGetVertex(ids[i])[1] * spacing);
						c->c = (z*spacing) + (MCGetVertex(ids[i])[2] * spacing);
					
						NORMAL* n = new NORMAL;
						n->a = 1;
						n->b = 1;
						n->c = 1;
					
						VERTEX v;
						v.pos = c;
						v.norm = n;
					
						vertices[vx_count] = v;
						indices[vx_count] = vx_count;
						vx_count += 1;
					}
				}
			}
		}
	}
	
	m_vbo->setData(vx_count, vertices, indices);
	
	printf("SoftwareMarchingCubes: %d vertices set out of a possible %d (%.3f%% fill)\n", vx_count, max_vxs, ((float)vx_count/max_vxs)*100);
	
	for(int i = 0; i < vx_count; i++)
	{
		delete vertices[i].pos;
		delete vertices[i].norm;
	}
	
	delete[] vertices;
	delete[] indices;
}

void SoftwareMarchingCubes::draw()
{
	m_vbo->draw();
}

int SoftwareMarchingCubes::index1D(int x, int y, int z)
{
	int i = (m_dim * m_dim * x) + (m_dim * y) + z;
	if(i >= m_dim * m_dim * m_dim)
	{
		fprintf(stderr, "SoftwareMarchingCubes error: invalid 1d index %d for x=%d y=%d z=%d, dim=%d\n", i, x, y, z, m_dim);
	}
	return i;
}
