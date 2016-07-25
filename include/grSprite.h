#ifndef HEADER_GRSPRITE
#define HEADER_GRSPRITE

#include "graphicsraptor.h"
#include "grResource.h"

GLfloat vertices[] = {
	// Pos      // Tex
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f
};

typedef struct grSprite
{
	grTexture texture;
	grVec2 size;
	grVec2 pos;
	grFloat rotation;
	grVec4 color;
} grSprite;

typedef struct grRenderer
{
	GLuint vbo;
	GLuint vao;
	grShader* shader;
} grRenderer;

grRenderer* grRendererAlloc();
grRenderer* grRendererInit(grRenderer* sprite);
void grRendererSprite(grRenderer* renderer, grSprite* sprite);

#endif