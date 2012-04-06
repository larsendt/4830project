#include "SoftwareMarchingCubes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "MCLookupTable.h"


/*SoftwareMarchingCubes::SoftwareMarchingCubes()
{
}

SoftwareMarchingCubes::~SoftwareMarchingCubes()
{
}

void SoftwareMarchingCubes::setNoiseData(unsigned char* noise, int dim, float spacing){

	m_noise = noise;
	m_dim = dim;
	m_spacing = spacing;

}

void SoftwareMarchingCubes::runOutToMesh(MeshObject * mesh)
{

	COORD3D cube[8];
	int index = 0;
	cube[index].x = 0; cube[index].y = 0; cube[index].z = 0;
	index = 1;
	cube[index].x = 1; cube[index].y = 0; cube[index].z = 0;
	index = 2;
	cube[index].x = 1; cube[index].y = 0; cube[index].z = 1;
	index = 3;
	cube[index].x = 0; cube[index].y = 0; cube[index].z = 1;
	index = 4;
	cube[index].x = 0; cube[index].y = 1; cube[index].z = 0;
	index = 5;
	cube[index].x = 1; cube[index].y = 1; cube[index].z = 0;
	index = 6;
	cube[index].x = 1; cube[index].y = 1; cube[index].z = 1;
	index = 7;
	cube[index].x = 0; cube[index].y = 1; cube[index].z = 1;
	
	// we start with 512 vertices and allocate more if necessary
	int max_vxs = 512;
	VERTEX* vertices = (VERTEX*) malloc(max_vxs * sizeof(*vertices));
	GLuint* indices = (GLuint*) malloc(max_vxs * sizeof(*indices)); 
	int vx_count = 0;
	bool color_flag = false;
	
	for(int x = 0; x < m_dim-1; x++)
	{
		for(int y = 0; y < m_dim-1; y++)
		{
			for(int z = 0; z < m_dim-1; z++)
			{
				unsigned char noisevals[8];
				unsigned int indices1d[8];
				unsigned int isolevel = 128;
				unsigned int cubeindex = 0;
				
				for(int i = 0; i < 8; i++)
				{
					indices1d[i] = index1D(x+cube[i].x, y+cube[i].y, z+cube[i].z);
					noisevals[i] = m_noise[indices1d[i]];
					
					if(noisevals[i] < isolevel) cubeindex |= (unsigned char)pow(2, i);
				}
			
				if(cubeindex != 0xff && cubeindex != 0x0)
				{
					unsigned char* ids = indexTable[cubeindex];
					int idcount = indexCountTable[cubeindex];
	
					for(int i = 0; i < idcount; i++)
					{
						COORD3D c;
						//c->a = (x*spacing) + (vertexTable[ids[i]][0]*spacing);
						//c->b = (y*spacing) + (vertexTable[ids[i]][1]*spacing);
						//c->c = (z*spacing) + (vertexTable[ids[i]][2]*spacing);
						
						int edge0 = edgeMap[ids[i]][0];
						int edge1 = edgeMap[ids[i]][1];
						COORD3D temp = vInterpolation(isolevel, cube[edge0], cube[edge1], noisevals[edge0], noisevals[edge1]);
						
						c.x = (x*m_spacing) + (temp.x*m_spacing);
						c.y = (y*m_spacing) + (temp.y*m_spacing);
						c.z = (z*m_spacing) + (temp.z*m_spacing);
						
						COORD3D n;
						n.x = 0;
						n.y = 1;
						n.z = 0;
						
						COORD2D xy;
						
						xy.s = (float)c.x/(float)m_dim;
						xy.t = (float)c.y/(float)m_dim;
						
						COORD2D xz;
						
						xz.s = (float)c.x/(float)m_dim;
						xz.t = (float)c.z/(float)m_dim;
						
						COORD2D yz;
						
						yz.s = (float)c.y/(float)m_dim;
						yz.t = (float)c.z/(float)m_dim;
						
						COLOR color;
						
						color.r = c.x;
						color.g = c.y;
						color.b = c.z;
						color.a = 1.0;
				
						// allocate more memory if necessary
						if(vx_count == max_vxs)
						{
							max_vxs *= 2;
							vertices = (VERTEX*) realloc(vertices, max_vxs * sizeof(*vertices));
							indices = (GLuint*) realloc(indices, max_vxs * sizeof(*indices));
						}
				
						vertices[vx_count].c = c;
						vertices[vx_count].n = n;
						vertices[vx_count].xy = xy;
						vertices[vx_count].xz = xz;
						vertices[vx_count].yz = yz;
						
						indices[vx_count] = vx_count;
						vx_count ++;
					}
					
					
					color_flag = false;
				}
			}
		}
	}
	
	/*printf("Generating normals\n");
	
	for (int i = 0; i<vx_count; i+=3){
	
	
		COORD3D a = vertices[i].c;
		COORD3D b = vertices[i+1].c;
		COORD3D c = vertices[i+2].c;
		
		a.x-=b.x;a.y-=b.y;a.z-=b.z;
		c.x-=b.x;c.y-=b.y;c.z-=b.z;
		
		COORD3D w;
		COORD3D u;
		
		w.x = a.x-c.x; w.y = a.y-c.y; w.z = a.z-c.z;
		u.x = a.x-b.x; u.y = a.y-b.y; u.z = a.z-b.z;
		
		COORD3D n;
		
		if (i%2 == 0){
			COORD3D p;
			p = w;
			w = u;
			u = p;
		}
		
		double x = (w.y*u.z)-(w.z*u.y);
		double y = (w.z*u.x)-(w.x*u.z);
		double z = (w.x*u.y)-(w.y*u.x);
		n.x = x; n.y = y; n.z = z;
		vertices[i].n = n;
		vertices[i+1].n = n;
		vertices[i+2].n = n;
		
	}*/
	
	
	/*printf("SoftwareMarchingCubes: %d vertices set out of a possible %d (%.3f%% fill)\n", vx_count, m_dim*m_dim*m_dim*12, ((float)vx_count/(m_dim*m_dim*m_dim*12))*100);
	
	mesh->setInterleaved(vertices, vx_count-1, indices, vx_count-1);
	
}

void SoftwareMarchingCubes::draw()
{
	printf("Can't draw this, doo dood oodo\n");
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
	p.x = p1.x + mu*(p2.x-p1.x);
	p.y = p1.y + mu*(p2.y-p1.y);
	p.z = p1.z + mu*(p2.z-p1.z);
	
	return p;
}
*/
