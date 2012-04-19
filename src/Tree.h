#define GL_GLEXT_PROTOTYPES
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "Types.h"

#ifndef TREE
#define TREE

#define BUFFER_OFFSET(i) ((char*) NULL + i)

struct tree_package{
	float x, y, z;        //Vertex
	float nx, ny, nz;     //Normal
	float s0, t0;         //Texcoord0
	float rigidity;
	float padding[7]; // 32-byte alignment for ATI
};

class Tree{
	public:
		Tree();
		~Tree();
		
		void setInterleaved(tree_package * vData, unsigned int v_count, unsigned int * indices, unsigned int i_count);
		void setShader(unsigned int program);
		void draw();
		void setWind(float x, float y, float z);
		
		unsigned int c_shader;
	private:
		
		unsigned int vbo_packages;
		
		unsigned int att_vertex;
		unsigned int att_normal;
		unsigned int att_tex;
		unsigned int att_rigidity;
		
		unsigned int uniform_wind;
				
		unsigned int ibo_elements;
};

#endif
