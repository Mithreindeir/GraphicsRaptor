#ifndef HEADER_GRSPRITE
#define HEADER_GRSPRITE

#include "graphicsraptor.h"
#include "grResource.h"

typedef struct grSprite
{
	GLuint vbo;
	grTexture texture;
} grSprite;

grSprite* grSpriteAlloc();
grSprite* grSpriteInit(grSprite* sprite);

#endif