#include "PostProcess.h"

void PostProcess::init(int width, int height){

	time = 0.0;

	W = width;
	H = height;
	
	// Initialize frame texture
	
	glGenTextures(1, &fbo_texture);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	
	
	// Initialize depth texture
	
	glGenTextures(1, &fbo_depth_tex);
	glBindTexture(GL_TEXTURE_2D, fbo_depth_tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	
	//glGenRenderbuffers(1, &rbo_depth);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	
	
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, fbo_depth_tex, 0);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);
	
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	
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
	
	glGenBuffers(1, &vbo_fbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_fbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices),fbo_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	const char * attribute_name = "v_coord";
	attribute_v_coord_postproc = glGetAttribLocation(fbo_shader->getID(), attribute_name);
	
	const char* uniform_name = "fbo_texture";
	uniform_fbo_texture = glGetUniformLocation(fbo_shader->getID(), uniform_name);
	glUniform1i(uniform_fbo_texture, 0);
	
	uniform_name = "fbo_depth_tex";
	uniform_fbo_depth_tex = glGetUniformLocation(fbo_shader->getID(), uniform_name);
	glUniform1i(uniform_fbo_depth_tex, 1);
	
	uniform_name = "dX";
	dxloc = glGetUniformLocation(fbo_shader->getID(), uniform_name);
	
	uniform_name = "dY";
	dyloc = glGetUniformLocation(fbo_shader->getID(), uniform_name);
	
	uniform_name = "time";
	timeloc = glGetUniformLocation(fbo_shader->getID(), uniform_name);
	
}

void PostProcess::draw(){
	
	time += .1;
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	float dX = 1.0/W;
   	float dY = 1.0/H;
	glUseProgram(fbo_shader->getID());
	glUniform1f(dxloc,dX);
    glUniform1f(dyloc,dY);
    glUniform1f(timeloc, time);
    
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glUniform1i(uniform_fbo_texture, 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fbo_depth_tex);
	glUniform1i(uniform_fbo_depth_tex, 1);
	
	glEnableVertexAttribArray(attribute_v_coord_postproc);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_fbo_vertices);
	glVertexAttribPointer(attribute_v_coord_postproc, 2, GL_FLOAT, GL_FALSE, 0 , 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0 , 4);
	glDisableVertexAttribArray(attribute_v_coord_postproc);
	
	glUseProgram(0);

}

void PostProcess::setShader(Shader * shader){
	fbo_shader = shader;
}

void PostProcess::resize(int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	
	glBindTexture(GL_TEXTURE_2D, fbo_depth_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	W = width;
	H = height;
	
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void PostProcess::startDraw(){

	glBindFramebuffer(GL_FRAMEBUFFER,fbo);

}
