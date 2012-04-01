#include <stdio.h>
#include <stdlib.h>
#define GL_GLEXT_PROTOTYPES
#ifndef USE_GLEW
	//#include <GL/glew.h>
#endif
#include <GL/gl.h>

#ifndef SHADER_FUNCS
#define SHADER_FUNCS

char* file_read(const char* filename);
void print_log(GLuint object);
GLint create_shader(const char* filename, GLenum type);

#endif
