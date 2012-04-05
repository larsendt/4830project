#include "Shader.h"
#include <GL/glu.h>
#include <stdio.h>
class PostProcess{

	public:
		
		void draw();
		void init(int width, int height);
		void startDraw();
		void resize(int width, int height);
		void setShader(Shader * shader);
	
	private:
		unsigned int W, H;
		Shader * fbo_shader;
		float time;
		unsigned int fbo, fbo_texture, fbo_depth_tex, rbo_depth;
		unsigned int vbo_fbo_vertices;
		unsigned int ppshader;
		unsigned int attribute_v_coord_postproc;
		unsigned int uniform_fbo_texture, uniform_fbo_depth_tex, uniform_offset;
		unsigned int dxloc, dyloc, timeloc;

};
