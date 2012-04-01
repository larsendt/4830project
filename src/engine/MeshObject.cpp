#include "MeshObject.h"

MeshObject::MeshObject(){
	//printf("prev: %s\n", gluErrorString(glGetError()));
	glGenBuffers(1, &vbo_vertices);
	//printf("verts: %s\n", gluErrorString(glGetError()));
	glGenBuffers(1, &vbo_normals);
	//printf("norms: %s\n", gluErrorString(glGetError()));
	glGenBuffers(1, &vbo_tex_yz);
	//printf("yz: %s\n", gluErrorString(glGetError()));
	glGenBuffers(1, &vbo_tex_xy);
	//printf("xy: %s\n", gluErrorString(glGetError()));
	glGenBuffers(1, &vbo_tex_xz);
	//printf("xz: %s\n", gluErrorString(glGetError()));
	glGenBuffers(1, &ibo_elements);
	//printf("ibos: %s\n", gluErrorString(glGetError()));
	
}

MeshObject::~MeshObject(){

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &vbo_normals);
	glDeleteBuffers(1, &vbo_tex_yz);
	glDeleteBuffers(1, &vbo_tex_xz);
	glDeleteBuffers(1, &vbo_tex_xy);
	glDeleteBuffers(1, &ibo_elements);

}

void MeshObject::set(vbo_data * cData){

	//printf("prev: %s\n", gluErrorString(glGetError()));

	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, cData->v_count*sizeof(float), cData->verts, GL_STATIC_DRAW);
	
	//printf("verts: %s\n", gluErrorString(glGetError()));
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, cData->n_count*sizeof(float), cData->norms, GL_STATIC_DRAW);
	
	//printf("norms: %s\n", gluErrorString(glGetError()));
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_yz);
	glBufferData(GL_ARRAY_BUFFER, cData->yz_count*sizeof(float), cData->yztex, GL_STATIC_DRAW);
	
	//printf("yz: %s\n", gluErrorString(glGetError()));
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_xz);
	glBufferData(GL_ARRAY_BUFFER, cData->xz_count*sizeof(float), cData->xztex, GL_STATIC_DRAW);
	
	//printf("xz: %s\n", gluErrorString(glGetError()));
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_xy);
	glBufferData(GL_ARRAY_BUFFER, cData->xy_count*sizeof(float), cData->xytex, GL_STATIC_DRAW);
	
	//printf("xy: %s\n", gluErrorString(glGetError()));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cData->i_count*sizeof(unsigned short), cData->vorder, GL_STATIC_DRAW);
	
	//printf("ibo: %s\n", gluErrorString(glGetError()));
	
	const char* attribute_name;
	attribute_name = "vertex";
	att_vertex = glGetAttribLocation(c_shader, attribute_name);
	if (att_vertex == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}

	
	attribute_name = "normal";
	att_normal = glGetAttribLocation(c_shader, attribute_name);
	if (att_normal == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	
	attribute_name = "tex_yz";
	att_tex_yz = glGetAttribLocation(c_shader, attribute_name);
	if (att_tex_yz == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	
	attribute_name = "tex_xz";
	att_tex_xz = glGetAttribLocation(c_shader, attribute_name);
	if (att_tex_xz == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	
	attribute_name = "tex_xy";
	att_tex_xy = glGetAttribLocation(c_shader, attribute_name);
	if (att_tex_xy == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	//printf("binding xy: %s\n", gluErrorString(glGetError()));
	

}

void MeshObject::setShader(unsigned int program){
	c_shader = program;
}

void MeshObject::draw(){
	
	glUseProgram(c_shader);
	
	//printf("prev: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glVertexAttribPointer(
		att_vertex, // attribute
		3,								 // number of elements per vertex, here (XYZ)
		GL_FLOAT,					// the type of each element
		GL_FALSE,					// take our values as-is
		0,								 // no extra data between each position
		0									// offset of first element
	);
	
	//printf("vert: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glVertexAttribPointer(
		att_normal, // attribute
		3,
		GL_FLOAT,
		GL_FALSE,
		0,		
		0		
	);
	
	//printf("norms: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_tex_yz);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_yz);
	glVertexAttribPointer(
		att_tex_yz, // attribute
		2,
		GL_FLOAT,
		GL_FALSE,
		0,		
		0		
	);
	
	//printf("yz: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_tex_xz);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_xz);
	glVertexAttribPointer(
		att_tex_xz, // attribute
		2,
		GL_FLOAT,
		GL_FALSE,
		0,		
		0		
	);
	
	//printf("xz: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_tex_xy);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_xy);
	glVertexAttribPointer(
		att_tex_xy, // attribute
		2,
		GL_FLOAT,
		GL_FALSE,
		0,		
		0		
	);
	
	//printf("xy: %s\n", gluErrorString(glGetError()));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	int size;	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size/sizeof(unsigned short), GL_UNSIGNED_SHORT, 0);
	
	//printf("draw: %s\n", gluErrorString(glGetError()));
	
	glDisableVertexAttribArray(att_tex_xy);
	glDisableVertexAttribArray(att_tex_xz);
	glDisableVertexAttribArray(att_tex_yz);
	glDisableVertexAttribArray(att_normal);
	glDisableVertexAttribArray(att_vertex);
	glUseProgram(0);
}
