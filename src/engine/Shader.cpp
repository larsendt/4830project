#include "Shader.h"
void Shader::load(char* vert, char* frag){
	//
	//
	//	Loads in a vertex and fragment shader, links them to the shader program
	//
	//
	GLint v = create_shader(vert, GL_VERTEX_SHADER);
	GLint f = create_shader(frag, GL_FRAGMENT_SHADER);
	program = glCreateProgram();
	glAttachShader(program, v);
	glAttachShader(program, f);
	glLinkProgram(program);
	GLint link_ok;
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		print_log(program);
	}
}

void Shader::shade(){

	glUseProgram(program);

}

void Shader::setAttrib(char* attribname){
	int tag = glGetAttribLocation(program, (const char*) attribname);
	if (tag == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribname);
	}
	std::string str(attribname);
	names[str] = tag;
}

void Shader::setUniform(char* uniformname){
	int tag = glGetUniformLocation(program, (const char*) uniformname);
	printf("%i\n", tag);
	if (tag == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", uniformname);
	}
	std::string str(uniformname);
	names[str] = tag;
}

void Shader::updateUniform1f(char* uniformname, float value){

	std::map<std::string,int>::iterator it;
	std::string str(uniformname);
	if ((it = names.find(str)) != names.end()){
		glUniform1f(it->second, value);
	}
	else {
		fprintf(stderr, "Can't find uniform %s", uniformname);
	}

}

void Shader::updateUniform1i(char* uniformname, int value){

	std::map<std::string,int>::iterator it;
	std::string str(uniformname);
	if ((it = names.find(str)) != names.end()){
		glUniform1i(it->second, value);
	}
	else {
		fprintf(stderr, "Can't find uniform %s", uniformname);
	}

}
