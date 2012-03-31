#ifndef VERTEX_BUFFER_OBJECT_H
#define VERTEX_BUFFER_OBJECT_H

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#include "Types.h"

class VertexBufferObject
{
	public:
		// the options for mode are GL_POINTS, GL_TRIANGLES, etc.. (see http://www.opengl.org/sdk/docs/man/xhtml/glDrawElements.xml, first parameter)
		VertexBufferObject(GLenum mode);
		VertexBufferObject(GLenum mode, int vertex_count, VERTEX* vertex_data, GLuint* index_data);
		~VertexBufferObject();
		
		void setData(int vertex_count, VERTEX* vertex_data, GLuint* index_data);
		void draw();
		void clear();
		
	private:
		GLuint m_vbo;
		GLuint m_ibo;
		GLenum m_mode;
		int m_vertexCount;
};

#endif
