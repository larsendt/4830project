#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <stdio.h>
#include "Vec3.h"

class Water{

	public:
		Water();
		void init(int width, int height);
		void setShader(unsigned int program){shader = program;};
		void render();
		vec3 getReflectionPosition(vec3 camera_pos, float &pitch);
		void protectDepthBuffer();
		void stencilBuffer(vec3 pos, float yaw, float pitch);
	private:
	
		
	
		unsigned int vbo_elements;
		
		unsigned int att_vertex;
		unsigned int att_normal;
		
		unsigned int W, H;
		
		unsigned int shader;
		
		unsigned int att_pp_vertex;
		unsigned int uniform_tex;
		unsigned int uniform_offset;
};
