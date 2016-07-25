#include "../include/grSprite.h"

grSprite * grSpriteAlloc()
{
	return malloc(sizeof(grSprite));
}

grSprite * grSpriteInit(grSprite * sprite)
{
	sprite->vbo = -1;
	glGenBuffers(1, &sprite->vbo);
	return sprite;
}

