#ifndef HEADER_GRSPRITE
#define HEADER_GRSPRITE

#include "graphicsraptor.h"
#include "grResource.h"
#include "grMath.h"
#include "grCamera.h"


typedef struct grQuad
{
	GLfloat* vertices;
} grQuad;
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
	grCamera* camera;
} grRenderer;

grQuad* grQuadAlloc();
grQuad* grQuadInit(grQuad* quad, grVec2 pos, grVec2 size, grSprite* sprite);

grSprite* grSpriteAlloc();
grSprite* grSpriteInit(grSprite* sprite, const char* file, int interpolate);
grRenderer* grRendererAlloc();
grRenderer* grRendererInit(grRenderer* sprite, grVec2 size);
void grRendererSprite(grRenderer* renderer, grSprite* sprite, grQuad* quad);

#endif