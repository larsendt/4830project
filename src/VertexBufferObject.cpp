#include "VertexBufferObject.h"
#include <stdio.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// don't use __internalVertex__ outside of this class (use the stuff in Types.h instead)
struct __internalVertex__ {
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
};

VertexBufferObject::VertexBufferObject(GLenum mode)
{
	m_vertexCount = 0;
	m_vbo = 0;
	m_ibo = 0;
	m_mode = mode;
}

VertexBufferObject::VertexBufferObject(GLenum mode, int vertex_count, VERTEX* vertex_data, GLuint* index_data)
{
	setData(vertex_count, vertex_data, index_data);	
	m_mode = mode;
}

VertexBufferObject::~VertexBufferObject()
{
	clear();
}

void VertexBufferObject::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(__internalVertex__), BUFFER_OFFSET(0));
	
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(__internalVertex__), BUFFER_OFFSET(sizeof(float) * 3));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(m_mode, m_vertexCount, GL_UNSIGNED_INT, 0);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void VertexBufferObject::clear()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}

void VertexBufferObject::setData(int vertex_count, VERTEX* vertex_data, GLuint* index_data)
{
	m_vertexCount = vertex_count;
	
	__internalVertex__* vertices = new __internalVertex__[m_vertexCount];
	
	for(int i = 0; i < m_vertexCount; i++)
	{
		__internalVertex__ v;
		v.x = vertex_data[i].pos->a;
		v.y = vertex_data[i].pos->b;
		v.z = vertex_data[i].pos->c;
		v.nx = vertex_data[i].norm->a;
		v.ny = vertex_data[i].norm->a;
		v.nz = vertex_data[i].norm->a;
		vertices[i] = v;
	}
	
	glGenBuffers(1, &m_vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount*sizeof(__internalVertex__), vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexCount*sizeof(GLuint), index_data, GL_STATIC_DRAW);
	
	delete[] vertices;
}
