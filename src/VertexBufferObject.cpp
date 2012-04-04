#include "VertexBufferObject.h"
#include <stdio.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

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
	glVertexPointer(3, GL_FLOAT, sizeof(VERTEX), BUFFER_OFFSET(0));
	
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(VERTEX), BUFFER_OFFSET(sizeof(COORD3D)));
	
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, sizeof(VERTEX), BUFFER_OFFSET(sizeof(COORD3D) + sizeof(NORMAL)));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(m_mode, m_vertexCount, GL_UNSIGNED_INT, 0);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void VertexBufferObject::clear()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}

void VertexBufferObject::setData(int vertex_count, VERTEX* vertex_data, GLuint* index_data)
{
	m_vertexCount = vertex_count;
	
	glGenBuffers(1, &m_vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount*sizeof(VERTEX), vertex_data, GL_STATIC_DRAW);
	
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexCount*sizeof(GLuint), index_data, GL_STATIC_DRAW);
}
