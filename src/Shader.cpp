#include "Shader.h"
#include "Util.h"
#include <stdlib.h>
#include <stdio.h>


Shader::Shader(const char* vert_path, const char* frag_path)
{
    printf("Compiling vertex shader: %s\n", vert_path);
    GLuint vertex_handle = compileShader(GL_VERTEX_SHADER, vert_path);
    printf("Compiling fragment shader: %s\n", frag_path);
    GLuint frag_handle = compileShader(GL_FRAGMENT_SHADER, frag_path);
    printf("Linking program\n");
    m_program = linkProgram(vertex_handle, frag_handle);
    printf("Complete\n");
}

void Shader::load(const char* vert_path, const char* frag_path){

	printf("Compiling vertex shader: %s\n", vert_path);
    GLuint vertex_handle = compileShader(GL_VERTEX_SHADER, vert_path);
    printf("Compiling fragment shader: %s\n", frag_path);
    GLuint frag_handle = compileShader(GL_FRAGMENT_SHADER, frag_path);
    printf("Linking program\n");
    m_program = linkProgram(vertex_handle, frag_handle);
    printf("Complete\n");

}
void Shader::bind()
{
    glUseProgram(m_program);
}

void Shader::release()
{
    glUseProgram(0);
}

GLuint Shader::getID(){
	return m_program;
}

void Shader::setUniform1f(const char* name, float value)
{
    GLint loc = glGetUniformLocation(m_program, name);
    glUniform1f(loc, value);
}

void Shader::setUniform2f(const char* name, float v1, float v2)
{
    GLint loc = glGetUniformLocation(m_program, name);
    glUniform2f(loc, v1, v2);
}

void Shader::setUniform3f(const char* name, float v1, float v2, float v3)
{
    GLint loc = glGetUniformLocation(m_program, name);
    glUniform3f(loc, v1, v2, v3);
}

void Shader::setUniform4f(const char* name, float v1, float v2, float v3, float v4)
{
    GLint loc = glGetUniformLocation(m_program, name);
    glUniform4f(loc, v1, v2, v3, v4);
}

void Shader::setUniform1i(const char* name, int value)
{
    GLint loc = glGetUniformLocation(m_program, name);
    glUniform1i(loc, value);
}

void Shader::setUniform2i(const char* name, int v1, int v2)
{
    GLint loc = glGetUniformLocation(m_program, name);
    glUniform2i(loc, v1, v2);
}

void Shader::setUniform3i(const char* name, int v1, int v2, int v3)
{
    GLint loc = glGetUniformLocation(m_program, name);
    glUniform3i(loc, v1, v2, v3);
}

void Shader::setUniform4i(const char* name, int v1, int v2, int v3, int v4)
{
    GLint loc = glGetUniformLocation(m_program, name);
    glUniform4i(loc, v1, v2, v3, v4);
}

void Shader::setUniformMatrix4fv(const char* name, float* value)
{
    GLint loc = glGetUniformLocation(m_program, name);
    glUniformMatrix4fv(loc, 1, false, value);
}

//----------------------------------------
//               Protected
//----------------------------------------

GLuint Shader::compileShader(GLenum shader_type, const char* file_path)
{
    std::string s = readFile(file_path);
    const char* shader_src = s.c_str();
    GLuint shader = glCreateShader(shader_type);
    GLint len = s.length();
    glShaderSource(shader, 1, &shader_src, &len);
    glCompileShader(shader);
    printShaderLog(shader, file_path);
    return shader;
}

GLuint Shader::linkProgram(GLuint vert_handle, GLuint frag_handle)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vert_handle);
    glAttachShader(program, frag_handle);
    glLinkProgram(program);
    printProgramLog(program);
    return program;
}

void Shader::printShaderLog(GLuint shader, const char* shader_file)
{
   	GLint log_length = 0;
	if (glIsShader(shader))
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(shader))
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &log_length);
	else {
		fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}

	char* log = (char*)malloc(log_length);

	if (glIsShader(shader))
		glGetShaderInfoLog(shader, log_length, NULL, log);
	else if (glIsProgram(shader))
		glGetProgramInfoLog(shader, log_length, NULL, log);

	fprintf(stderr, "%s", log);
	free(log);
}

void Shader::printProgramLog(GLuint program)
{
    GLint log_length = 0;
	if (glIsShader(program))
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(program))
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
	else {
		fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}

	char* log = (char*)malloc(log_length);

	if (glIsShader(program))
		glGetShaderInfoLog(program, log_length, NULL, log);
	else if (glIsProgram(program))
		glGetProgramInfoLog(program, log_length, NULL, log);

	fprintf(stderr, "%s", log);
	free(log);
}













