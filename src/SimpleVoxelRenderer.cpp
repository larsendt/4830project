#include "SimpleVoxelRenderer.h"
#include <stdio.h>

SimpleVoxelRenderer::SimpleVoxelRenderer()
{
	m_vbo = new VertexBufferObject(GL_POINTS);
}

SimpleVoxelRenderer::~SimpleVoxelRenderer()
{
	delete m_vbo;
}

void SimpleVoxelRenderer::setVoxelData(VOXEL* voxels, int count)
{
	m_voxelCount = count;
	
	VERTEX* vertices = new VERTEX[m_voxelCount];
	GLuint* indices = new GLuint[m_voxelCount];
	
	for(int i = 0; i < m_voxelCount; i++)
	{
		VERTEX v;
		NORMAL* n = new NORMAL;
		v.pos = voxels[i].pos;
		
		n->a = 1.0;
		n->b = 0.0;
		n->c = 0.0;
		
		v.norm = n;
		
		vertices[i] = v;
		indices[i] = i;
	}
	
	m_vbo->setData(m_voxelCount, vertices, indices);
	delete[] indices;
	
	for(int i = 0; i < m_voxelCount; i++)
	{
		delete vertices[i].norm;
	}
	
	delete[] vertices;
}

void SimpleVoxelRenderer::draw()
{
	m_vbo->draw();
}
