#include "Mesh.h"

Mesh::Mesh(){

	glGenBuffers(1, &mesh_packages);

	glGenBuffers(1, &ibo_elements);
	
}

Mesh::~Mesh(){

	glDeleteBuffers(1, &mesh_packages);

	glDeleteBuffers(1, &ibo_elements);

}


void Mesh::setInterleaved(mesh_package * vData, unsigned int v_count, 
							unsigned int * indices, unsigned int i_count){

	
	glUseProgram(m_shader);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh_packages);
	glBufferData(GL_ARRAY_BUFFER,
					v_count*sizeof(mesh_package), // size in bytes
					&vData[0].x, // address of first element
					GL_STATIC_DRAW); // derp a herp derp derp
		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					i_count*sizeof(unsigned int),
					indices,
					GL_STATIC_DRAW);

	const char* attribute_name;
	attribute_name = "vertex";
	att_vertex = glGetAttribLocation(m_shader, attribute_name);
	if (att_vertex == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}

	
	attribute_name = "normal";
	att_normal = glGetAttribLocation(m_shader, attribute_name);
	if (att_normal == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	free(indices);
	free(vData);

}

void Mesh::setShader(unsigned int program){
	m_shader = program;
}

void Mesh::draw(){
	
	glEnableVertexAttribArray(att_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_packages);
	glVertexAttribPointer(
		att_vertex, // attribute
		3,							 // number of elements per vertex, here (XYZ)
		GL_FLOAT,					// the type of each element
		GL_FALSE,					// take our values as-is
		sizeof(mesh_package),								 // no extra data between each position
		BUFFER_OFFSET(0)									// offset of first element
	);
	
	glEnableVertexAttribArray(att_normal);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_packages);
	glVertexAttribPointer(
		att_normal, // attribute
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(mesh_package),		
		BUFFER_OFFSET(12)		
	);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	int size;	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLE_STRIP, size/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	
	glDisableVertexAttribArray(att_normal);
	glDisableVertexAttribArray(att_vertex);
}
