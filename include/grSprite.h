#ifndef HEADER_GRSPRITE
#define HEADER_GRSPRITE

#include "graphicsraptor.h"
#include "grResource.h"
#include "grMath.h"


typedef struct grSprite
{
	grTexture* texture;
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

grSprite* grSpriteAlloc();
grSprite* grSpriteInit(grSprite* sprite, const char* file);
grRenderer* grRendererAlloc();
grRenderer* grRendererInit(grRenderer* sprite);
void grRendererSprite(grRenderer* renderer, grSprite* sprite);

#endif