#define GL_GLEXT_PROTOTYPES
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef MESHOBJECT
#define MESHOBJECT

struct vbo_data{

	float* verts;
	int v_count;
	float* norms;
	int n_count;
	float* yztex;
	int yz_count;
	float* xztex;
	int xz_count;
	float* xytex;
	int xy_count;
	unsigned short * vorder;
	int i_count;
};

class MeshObject{
	public:
		MeshObject();
		~MeshObject();
		
		void set(vbo_data * cData);
		void setShader(unsigned int program);
		void draw();
		
		unsigned int c_shader;
	private:
		
		int x;
		int y;
		int z;
		
		unsigned int vbo_vertices;
		unsigned int att_vertex;
		unsigned int vbo_normals;
		unsigned int att_normal;
		unsigned int vbo_tex_yz;
		unsigned int att_tex_yz;
		unsigned int vbo_tex_xz;
		unsigned int att_tex_xz;
		unsigned int vbo_tex_xy;
		unsigned int att_tex_xy;
		unsigned int ibo_elements;
};

#endif
