#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>

class Skybox
{
	public:
		Skybox();
		void draw();
	
	private:
		GLuint m_tex;
		GLuint m_displayList;
		GLUquadricObj* m_sphere;
};

