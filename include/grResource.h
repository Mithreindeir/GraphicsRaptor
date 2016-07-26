#ifndef HEADER_GRRESOURCE
#define HEADER_GRRESOURCE
#include "graphicsraptor.h"
#include "grMath.h"
#include <SOIL.h>

typedef struct grTexture
{
	GLuint id;
	int width, height;
	int internal_f;
	int image_f;
} grTexture;

typedef struct grShader
{
	GLuint id;
} grShader;

grTexture* grTextureAlloc();
grTexture* grTextureInit(grTexture* texture, GLuint w, GLuint h, unsigned char* dat);
grTexture* grTextureLoadFromFile(grTexture* texture, const char* file, int alpha);

grShader* grShaderAlloc();
grShader* grShaderInit(grShader* shader);
void grShaderUse(grShader* shader);
void grShaderCompile(grShader* shader, const GLchar * vs, const GLchar * fs);
void grShaderSetFloat(grShader* shader, const GLchar* name, GLfloat f);
void grShaderSetInteger(grShader* shader, const GLchar* name, GLint f);
void grShaderSetVec4(grShader* shader, const GLchar* name, grVec4 v);
void grShaderSetMat4(grShader* shader, const GLchar* name, const grMat4* f);

#endif