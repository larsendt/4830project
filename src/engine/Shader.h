

#include <stdio.h>
#include <map>
#include <string>

#include "shaderfuncs.h"
#ifndef SHADER_CLASS
#define SHADER_CLASS
class Shader{
	public:
		void load(char* vert, char* frag);
		void shade();
		void setAttrib(char* attribname);
		void setUniform(char* uniformname);
		void updateUniform1f(char* uniformname, float value);
		void updateUniform1i(char* uniformname, int value);
		std::map<std::string, int> names;
		int program;
};

#endif
