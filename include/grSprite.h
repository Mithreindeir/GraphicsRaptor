#ifndef HEADER_GRSPRITE
#define HEADER_GRSPRITE

#include "graphicsraptor.h"

typedef struct grTexture
{
	GLuint id;
	int width, height;
} grTexture;

typedef struct grSprite
{
	GLuint vbo;
	grTexture texture;
} grSprite;

grSprite* grSpriteAlloc();
grSprite* grSpriteInit(grSprite* sprite);


#endif