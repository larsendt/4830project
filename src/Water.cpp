#include "Water.h"

Water::Water(int width, int height){

	// Initialize frame texture
	
	W = width;
	H = height;
	
	glGenTextures(1, &fbo_texture);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	
	// create framebuffer
	
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
	
	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE){
	
		fprintf(stderr, "fbo status error %u", status);
		fprintf(stderr, " code %u\n", GL_FRAMEBUFFER_COMPLETE); 
	
	}
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	
	GLfloat fbo_vertices[] = {
	
		-1,-1,
		 1,-1,
		-1, 1,
		 1, 1
	
	};

	glGenBuffers(1, &vbo_elements);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_elements);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices),fbo_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	const char * attribute_name = "vertex";
	att_pp_vertex = glGetAttribLocation(vboshader, attribute_name);
	
	const char* uniform_name = "fbo_texture";
	uniform_tex = glGetUniformLocation(vboshader, uniform_name);
	glUniform1i(uniform_tex, 0);

}

void Water::bindReflection(){

	glBindFramebuffer(GL_FRAMEBUFFER,fbo);

}

vec3 Water::getReflectionPosition(vec3 camera_pos){
	// THIS ASSUMES WATER AT 0 Y LEVEL
	camera_pos.y *= -1;
	return camera_pos;
}

void Water::render(){

	glUseProgram(vboshader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glUniform1i(fbo_texture, 0);
	
	glEnableVertexAttribArray(att_pp_vertex);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_elements);
	glVertexAttribPointer(att_pp_vertex, 2, GL_FLOAT, GL_FALSE, 0 , 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0 , 4);
	glDisableVertexAttribArray(att_pp_vertex);
	
	glUseProgram(0);
	
}

void Water::unbindReflection(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
