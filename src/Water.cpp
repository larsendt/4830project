#include "Water.h"

Water::Water(){

	
}

void Water::init(int width, int height){
// Initialize frame texture
	
	
	GLfloat vertices[] = {
	
		 -128,  0,-128,
		 128,0,-128,
		 -128,  0, 128,
		 128,0, 128
	
	};

	glGenBuffers(1, &vbo_elements);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_elements);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	const char * attribute_name = "vertex";
	att_pp_vertex = glGetAttribLocation(shader, attribute_name);
}

vec3 Water::getReflectionPosition(vec3 camera_pos, float &pitch){
	// THIS ASSUMES WATER AT 0 Y LEVEL
	camera_pos.y *= -1;
	pitch = -pitch;
	return camera_pos;
}

void Water::protectDepthBuffer(){
	glClear(GL_DEPTH_BUFFER_BIT);
	
	unsigned char save_color_mask[4];
	unsigned char save_depth_mask;
	
	glGetBooleanv(GL_COLOR_WRITEMASK,save_color_mask);
	glGetBooleanv(GL_DEPTH_WRITEMASK, &save_depth_mask);
	
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_TRUE);
	
	render();
	
	glColorMask(save_color_mask[0], save_color_mask[1], save_color_mask[2], save_color_mask[3]);
	glDepthMask(save_depth_mask);
	
}

void Water::stencilBuffer(vec3 pos, float yaw, float pitch){
	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
	glDepthMask(GL_FALSE);
	glStencilFunc(GL_NEVER,0,0xFF);
	glStencilOp(GL_INCR,GL_KEEP,GL_KEEP);
	
	glClear(GL_STENCIL_BUFFER_BIT);
	
	glPushMatrix();
	glLoadIdentity();
	
	glRotatef(-pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);

	glTranslatef(-pos.x, -pos.y, -pos.z);
	
	glPopMatrix();
	
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
	
	glStencilFunc(GL_LEQUAL,1,0xFF);
	
	float ref_pitch = pitch;
	vec3 ref_pos = getReflectionPosition(pos, ref_pitch);
	
	glPushMatrix();
	glLoadIdentity();
	
	glRotatef(-ref_pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);

	glTranslatef(-ref_pos.x, -ref_pos.y, -ref_pos.z);
	
	
	glPopMatrix();
	
}

void Water::render(){
	glUseProgram(shader);
	
	glEnableVertexAttribArray(att_pp_vertex);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_elements);
	glVertexAttribPointer(att_pp_vertex, 3, GL_FLOAT, GL_FALSE, 0 , 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0 , 4);
	glDisableVertexAttribArray(att_pp_vertex);
	
	glUseProgram(0);
}
