#ifndef HEADER_GRRESOURCE
#define HEADER_GRRESOURCE
#include "graphicsraptor.h"
#include "grMath.h"

typedef struct grTexture
{
	GLuint id;
	int width, height;
} grTexture;

typedef struct grShader
{
	GLuint id;
} grShader;

grShader* grShaderAlloc();
grShader* grShaderInit(grShader* shader);
void grShaderCompile(grShader* shader, const GLchar * vs, const GLchar * fs);
void grShaderSetFloat(grShader* shader, const GLchar* name, GLfloat f);
void grShaderSetInteger(grShader* shader, const GLchar* name, GLint f);
void grShaderSetVec4(grShader* shader, const GLchar* name, grVec4 v);
void grShaderSetMat4(grShader* shader, const GLchar* name, grMat4 f);

#endif