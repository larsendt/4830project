#include "SoftwareMarchingCubes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

	COORD3D cube[8];
	int index = 0;
	cube[index].a = 0; cube[index].b = 0; cube[index].c = 0;
	index = 1;
	cube[index].a = 1; cube[index].b = 0; cube[index].c = 0;
	index = 2;
	cube[index].a = 1; cube[index].b = 0; cube[index].c = 1;
	index = 3;
	cube[index].a = 0; cube[index].b = 0; cube[index].c = 1;
	index = 4;
	cube[index].a = 0; cube[index].b = 1; cube[index].c = 0;
	index = 5;
	cube[index].a = 1; cube[index].b = 1; cube[index].c = 0;
	index = 6;
	cube[index].a = 1; cube[index].b = 1; cube[index].c = 1;
	index = 7;
	cube[index].a = 0; cube[index].b = 1; cube[index].c = 1;
	
	m_dim = dim;
	
	// we start with 512 vertices and allocate more if necessary
	int max_vxs = 512;
	VERTEX* vertices = (VERTEX*) malloc(max_vxs * sizeof(*vertices));
	GLuint* indices = (GLuint*) malloc(max_vxs * sizeof(*indices)); 
	int vx_count = 0;
	bool color_flag = false;
	
	for(int x = 0; x < dim-1; x++)
	{
		for(int y = 0; y < dim-1; y++)
		{
			for(int z = 0; z < dim-1; z++)
			{
				unsigned char noisevals[8];
				unsigned int indices1d[8];
				unsigned int isolevel = 128;
				unsigned int cubeindex = 0;
				
				for(int i = 0; i < 8; i++)
				{
					indices1d[i] = index1D(x+cube[i].a, y+cube[i].b, z+cube[i].c);
					noisevals[i] = noise[indices1d[i]];
					
					if(noisevals[i] < isolevel) cubeindex |= (unsigned char)pow(2, i);
				}
			
				if(cubeindex != 0xff && cubeindex != 0x0)
				{
					unsigned char* ids = indexTable[cubeindex];
					int idcount = indexCountTable[cubeindex];
	
					for(int i = 0; i < idcount; i++)
					{
						COORD3D* c = new COORD3D;
						//c->a = (x*spacing) + (vertexTable[ids[i]][0]*spacing);
						//c->b = (y*spacing) + (vertexTable[ids[i]][1]*spacing);
						//c->c = (z*spacing) + (vertexTable[ids[i]][2]*spacing);
						
						int edge0 = edgeMap[ids[i]][0];
						int edge1 = edgeMap[ids[i]][1];
						COORD3D temp = vInterpolation(isolevel, cube[edge0], cube[edge1], noisevals[edge0], noisevals[edge1]);
						
						c->a = (x*spacing) + (temp.a*spacing);
						c->b = (y*spacing) + (temp.b*spacing);
						c->c = (z*spacing) + (temp.c*spacing);
						
						NORMAL* n = new NORMAL;
						n->a = 1;
						n->b = 1;
						n->c = 1;
						
						COLOR* color = new COLOR;
						
						color->r = c->a;
						color->g = c->b;
						color->b = c->c;
						color->a = 1.0;
				
						// allocate more memory if necessary
						if(vx_count == max_vxs)
						{
							max_vxs *= 2;
							vertices = (VERTEX*) realloc(vertices, max_vxs * sizeof(*vertices));
							indices = (GLuint*) realloc(indices, max_vxs * sizeof(*indices));
						}
				
						vertices[vx_count].pos = c;
						vertices[vx_count].norm = n;
						vertices[vx_count].color = color;
						indices[vx_count] = vx_count;
						vx_count ++;
					}
					
					
					color_flag = false;
				}
			}
		}
	}
	
	m_vbo->setData(vx_count, vertices, indices);
	
	printf("SoftwareMarchingCubes: %d vertices set out of a possible %d (%.3f%% fill)\n", vx_count, dim*dim*dim*12, ((float)vx_count/(dim*dim*dim*12))*100);
	
	for(int i = 0; i < vx_count; i++)
	{
		delete vertices[i].pos;
		delete vertices[i].norm;
	}
	
	free(vertices);
	free(indices);
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

COORD3D SoftwareMarchingCubes::vInterpolation(unsigned int isolevel,
								 COORD3D p1,
								 COORD3D p2,
								 unsigned char v1,
								 unsigned char v2)
{
	double mu;
	COORD3D p;
	
	if (fabs(isolevel-v1)<0.00001) return p1;
	if (fabs(isolevel-v2)<0.00001) return p2;
	if (fabs(v1-v2) < 0.00001) return p1;
	mu = (isolevel - v1) / (v2-v1);
	p.a = p1.a + mu*(p2.a-p1.a);
	p.b = p1.b + mu*(p2.b-p1.b);
	p.c = p1.c + mu*(p2.c-p1.c);
	
	return p;
}

