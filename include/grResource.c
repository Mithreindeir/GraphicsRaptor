#include "grResource.h"

grShader * grShaderAlloc()
{
	return malloc(sizeof(grShader));
}

grShader * grShaderInit(grShader * shader)
{
	shader->id = -1;
	return shader;
}

void grShaderCompile(grShader * shader, const GLchar * vs, const GLchar * fs)
{
	GLuint v, f;
	v = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v, 1, &vs, NULL);
	glCompileShader(v);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f, 1, &fs, NULL);
	glCompileShader(f);
	shader->id = glCreateProgram();
	glAttachShader(shader->id, v);
	glAttachShader(shader->id, f);
	glLinkProgram(shader->id);
	glDeleteShader(v);
	glDeleteShader(f);
}

void grShaderSetFloat(grShader * shader, const GLchar * name, GLfloat f)
{
	glUniform1f(glGetUniformLocation(shader->id, name), f);
}

void grShaderSetInteger(grShader * shader, const GLchar * name, GLint i)
{
	glUniform1i(glGetUniformLocation(shader->id, name), i);
}

void grShaderSetVec4(grShader * shader, const GLchar * name, grVec4 v)
{
	glUniform4f(glGetUniformLocation(shader->id, name), v.x, v.y, v.z, v.w);
}

void grShaderSetMat4(grShader * shader, const GLchar * name, grMat4 m)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, grMat4Ptr(m));
}