#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "Types.h"

#define BUFFER_OFFSET(i) ((char*) NULL + i)


struct mesh_package{
	float x, y, z;        //Vertex
	float nx, ny, nz;     //Normal
	float padding[2]; // 32-byte alignment for ATI
};

class Mesh{
	public:
		Mesh();
		~Mesh();
		
		void setInterleaved(mesh_package * vData, unsigned int v_count, unsigned int * indiced, unsigned int i_count);
		void setShader(unsigned int program);
		void draw();
		
		unsigned int m_shader;
	private:
		
		unsigned int mesh_packages;
		
		unsigned int att_vertex;
		unsigned int att_normal;
		
		unsigned int ibo_elements;
};
