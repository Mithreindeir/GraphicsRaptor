#include "../include/grSprite.h"

grSprite * grSpriteAlloc()
{
	return malloc(sizeof(grSprite));
}

grSprite * grSpriteInit(grSprite * sprite)
{
	sprite->vbo = -1.0;
	glGenBuffers(1, &sprite->vbo);
	static_assert(1);
	return sprite;
}
