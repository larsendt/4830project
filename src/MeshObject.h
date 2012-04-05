#define GL_GLEXT_PROTOTYPES
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "Types.h"

#ifndef MESHOBJECT
#define MESHOBJECT

#define BUFFER_OFFSET(i) ((char*) NULL + i)

struct vbo_data{

	float* verts;
	float* norms;
	float* yztex;
	float* xztex;
	float* xytex;
	int v_count; // actually the number of elements in verts
	
	unsigned int * vorder;
	int i_count;
};

struct vbo_package{
	float x, y, z;        //Vertex
	float nx, ny, nz;     //Normal
	float s0, t0;         //Texcoord0
	float s1, t1;         //Texcoord1
	float s2, t2;         //Texcoord2
	float padding[4]; // 32-byte alignment for ATI
};

class MeshObject{
	public:
		MeshObject();
		~MeshObject();
		
		void setSequenced(vbo_data * vData);
		void setInterleaved(VERTEX * vData, unsigned int v_count, unsigned int * indiced, unsigned int i_count);
		void setShader(unsigned int program);
		void draw();
		
		unsigned int c_shader;
	private:
		
		unsigned int vbo_packages;
		
		unsigned int att_vertex;
		unsigned int att_normal;
		unsigned int att_tex_yz;
		unsigned int att_tex_xz;
		unsigned int att_tex_xy;
		
		unsigned int ibo_elements;
};

#endif
