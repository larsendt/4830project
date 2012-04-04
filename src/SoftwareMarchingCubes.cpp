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
	// maximum possible is dim*dim*dim voxels times a maximum of 12 vertices per voxel
	// TODO: we'll never hit this limit, so set things up to use a smaller inital amount and expand if necessary
	int max_vxs = dim*dim*dim*12;
	VERTEX* vertices = new VERTEX[max_vxs];
	GLuint* indices = new GLuint[max_vxs];
	int vx_count = 0;
	
	COORD3D vertlist[12];
	
	for(int x = 0; x < dim-1; x++)
	{
		for(int y = 0; y < dim-1; y++)
		{
			for(int z = 0; z < dim-1; z++)
			{
				unsigned int i0 = index1D(x+cube[0].a, y+cube[0].b, z+cube[0].c);
				unsigned int i1 = index1D(x+cube[1].a, y+cube[1].b, z+cube[1].c);
				unsigned int i2 = index1D(x+cube[2].a, y+cube[2].b, z+cube[2].c);
				unsigned int i3 = index1D(x+cube[3].a, y+cube[3].b, z+cube[3].c);
				unsigned int i4 = index1D(x+cube[4].a, y+cube[4].b, z+cube[4].c);
				unsigned int i5 = index1D(x+cube[5].a, y+cube[5].b, z+cube[5].c);
				unsigned int i6 = index1D(x+cube[6].a, y+cube[6].b, z+cube[6].c);
				unsigned int i7 = index1D(x+cube[7].a, y+cube[7].b, z+cube[7].c);
				
				unsigned char n0 = noise[i0];
				unsigned char n1 = noise[i1];
				unsigned char n2 = noise[i2];
				unsigned char n3 = noise[i3];
				unsigned char n4 = noise[i4];
				unsigned char n5 = noise[i5];
				unsigned char n6 = noise[i6];
				unsigned char n7 = noise[i7];
				
				unsigned char accum = 0x0;
				
				unsigned int isolevel = 128;
				unsigned int cubeindex = 0;
				if (n0 < isolevel) cubeindex |= 1;
				if (n1 < isolevel) cubeindex |= 2;
				if (n2 < isolevel) cubeindex |= 4;
				if (n3 < isolevel) cubeindex |= 8;
				if (n4 < isolevel) cubeindex |= 16;
				if (n5 < isolevel) cubeindex |= 32;
				if (n6 < isolevel) cubeindex |= 64;
				if (n7 < isolevel) cubeindex |= 128;
				
				
				accum = cubeindex;
				if(accum != 0xff && accum != 0x0)
				{
					unsigned char* ids = MCIndices[accum];
					int idcount = numVertsTable[accum];
					
					/////// BOTTOM FOUR //////
					
					if (edgeTable[accum] & 1){
						vertlist[0] = getEdgeVertex(0);
					}
					if (edgeTable[accum] & 2){
						vertlist[1] = getEdgeVertex(1);
					}
					if (edgeTable[accum] & 4){
						vertlist[2] = getEdgeVertex(2);
					}
					if (edgeTable[accum] & 8){
						vertlist[3] = getEdgeVertex(3);
					}
					
					/////// TOP FOUR ///////
					
					if (edgeTable[accum] & 16){
						vertlist[4] = getEdgeVertex(4);
					}
					if (edgeTable[accum] & 32){
						vertlist[5] = getEdgeVertex(5);
					}
					if (edgeTable[accum] & 64){
						vertlist[6] = getEdgeVertex(6);
					}
					if (edgeTable[accum] & 128){
						vertlist[7] = getEdgeVertex(7);
					}
					
					/////// FOUR SIDES //////
					
					if (edgeTable[accum] & 256){
						vertlist[8] = getEdgeVertex(8);
					}
					if (edgeTable[accum] & 512){
						vertlist[9] = getEdgeVertex(9);
					}
					if (edgeTable[accum] & 1024){
						vertlist[10] = getEdgeVertex(10);
					}
					if (edgeTable[accum] & 2048){
						vertlist[11] = getEdgeVertex(11);
					}
					for (int i = 0; ids[i]!=255;i+=3){
						for (int j = 0; j<3; j++){
							
							COORD3D* c = new COORD3D;
							c->a = (x*spacing) + (vertlist[i+j].a * spacing);
							c->b = (y*spacing) + (vertlist[i+j].b * spacing);
							c->c = (z*spacing) + (vertlist[i+j].c * spacing);
							
							NORMAL* n = new NORMAL;
							n->a = 1;
							n->b = 1;
							n->c = 1;
					
							vertices[vx_count].pos = c;
							vertices[vx_count].norm = n;
							indices[vx_count] = vx_count;
							vx_count ++;
						}
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

COORD3D SoftwareMarchingCubes::getEdgeVertex(int edgenum){

	COORD3D p;	
	p.a = MCVertices[edgenum][0];
	p.b = MCVertices[edgenum][1];
	p.c = MCVertices[edgenum][2];
	return p;

}
