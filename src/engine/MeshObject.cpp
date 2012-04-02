#include "MeshObject.h"

MeshObject::MeshObject(){

	glGenBuffers(1, &vbo_packages);

	glGenBuffers(1, &ibo_elements);
	
}

MeshObject::~MeshObject(){

	glDeleteBuffers(1, &vbo_packages);

	glDeleteBuffers(1, &ibo_elements);

}

void MeshObject::set(vbo_data * vData){

	int count = vData->v_count/3;
	vbo_package * packs = new vbo_package[count];
	int vc = 0;
	int nc = 0;
	int xyc = 0;
	int xzc = 0;
	int yzc = 0;
	
	float * dVerts = vData->verts;
	float * dNorms = vData->norms;
	float * dXY = vData->yztex;
	float * dXZ = vData->xztex;
	float * dYZ = vData->yztex;
	
	unsigned int offsetInByte;
	
	for (int i = 0; i < count; i++){
		vbo_package * p = &packs[i];
		p->x = dVerts[vc];
		vc++;
		p->y = dVerts[vc];
		vc++;
		p->z = dVerts[vc];
		vc++;
		
		p->nx = dNorms[nc];
		nc++;
		p->ny = dNorms[nc];
		nc++;
		p->nz = dNorms[nc];
		nc++;
		
		p->s0 = dXY[xyc];
		xyc++;
		p->t0 = dXY[xyc];
		xyc++;
		
		p->s1 = dXZ[xzc];
		xzc++;
		p->t1 = dXZ[xzc];
		xzc++;
		
		p->s2 = dXZ[yzc];
		yzc++;
		p->t2 = dXZ[yzc];
		yzc++;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glBufferData(GL_ARRAY_BUFFER,
					count*sizeof(vbo_package), // size in bytes
					&packs[0].x, // address of first element
					GL_STATIC_DRAW); // derp a herp derp derp
					
	unsigned short * indices = vData->vorder;
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					vData->i_count*sizeof(unsigned short),
					indices,
					GL_STATIC_DRAW);

	
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
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glVertexAttribPointer(
		att_vertex, // attribute
		3,								 // number of elements per vertex, here (XYZ)
		GL_FLOAT,					// the type of each element
		GL_FALSE,					// take our values as-is
		sizeof(vbo_package),								 // no extra data between each position
		BUFFER_OFFSET(0)									// offset of first element
	);
	
	//printf("vert: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glVertexAttribPointer(
		att_normal, // attribute
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vbo_package),		
		BUFFER_OFFSET(12)		
	);
	
	//printf("norms: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_tex_yz);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glVertexAttribPointer(
		att_tex_yz, // attribute
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vbo_package),		
		BUFFER_OFFSET(24)			
	);
	
	//printf("yz: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_tex_xz);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glVertexAttribPointer(
		att_tex_xz, // attribute
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vbo_package),		
		BUFFER_OFFSET(32)			
	);
	
	//printf("xz: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_tex_xy);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glVertexAttribPointer(
		att_tex_xy, // attribute
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vbo_package),		
		BUFFER_OFFSET(40)		
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
