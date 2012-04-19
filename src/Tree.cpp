#include "Tree.h"

Tree::Tree(){

	glGenBuffers(1, &vbo_packages);

	glGenBuffers(1, &ibo_elements);
	
}

Tree::~Tree(){

	glDeleteBuffers(1, &vbo_packages);

	glDeleteBuffers(1, &ibo_elements);

}


void Tree::setInterleaved(tree_package * vData, unsigned int v_count, 
							unsigned int * indices, unsigned int i_count){

	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glBufferData(GL_ARRAY_BUFFER,
					v_count*sizeof(tree_package), // size in bytes
					&vData[0].x, // address of first element
					GL_STATIC_DRAW); // derp a herp derp derp

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					i_count*sizeof(unsigned int),
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
	
	
	attribute_name = "tex";
	att_tex = glGetAttribLocation(c_shader, attribute_name);
	if (att_tex == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	
	attribute_name = "rigidity";
	att_rigidity = glGetAttribLocation(c_shader, attribute_name);
	if (att_rigidity == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	const char * uniform_name;
	
	uniform_name = "wind";
	uniform_wind = glGetUniformLocation(c_shader, uniform_name);
	if (uniform_wind == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
	printf("hi\n");
	//free(indices);
	//free(vData);
	printf("bye\n");

}

void Tree::setShader(unsigned int program){
	c_shader = program;
}

void Tree::setWind(float x, float y, float z){

	glUseProgram(c_shader);
	glUniform3f(uniform_wind, x, y, z);

}

void Tree::draw(){
	
	glUseProgram(c_shader);
	
	glEnableVertexAttribArray(att_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glVertexAttribPointer(
		att_vertex, // attribute
		3,								 // number of elements per vertex, here (XYZ)
		GL_FLOAT,					// the type of each element
		GL_FALSE,					// take our values as-is
		sizeof(tree_package),								 // no extra data between each position
		BUFFER_OFFSET(0)									// offset of first element
	);
	
	glEnableVertexAttribArray(att_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glVertexAttribPointer(
		att_normal, // attribute
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(tree_package),		
		BUFFER_OFFSET(12)		
	);
	
	//printf("norms: %s\n", gluErrorString(glGetError()));
	
	glEnableVertexAttribArray(att_tex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glVertexAttribPointer(
		att_tex, // attribute
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(tree_package),		
		BUFFER_OFFSET(24)			
	);
	
	glEnableVertexAttribArray(att_rigidity);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_packages);
	glVertexAttribPointer(
		att_rigidity, // attribute
		1,
		GL_FLOAT,
		GL_FALSE,
		sizeof(tree_package),		
		BUFFER_OFFSET(32)		
	);
	
	//printf("xy: %s\n", gluErrorString(glGetError()));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	int size;	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	
	glDisableVertexAttribArray(att_tex);
	glDisableVertexAttribArray(att_rigidity);
	glDisableVertexAttribArray(att_normal);
	glDisableVertexAttribArray(att_vertex);
	glUseProgram(0);
}
