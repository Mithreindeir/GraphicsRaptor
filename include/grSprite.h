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
	int frames;
	int currentFrame;
	grFloat speed;
	grQuad** quads;
	grFloat frame_time;
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
void grSpriteSetUpAnimation(grSprite* sprite, int cols, int rows);
void grSpriteUpdate(grSprite* sprite, grFloat dt);
grRenderer* grRendererAlloc();
grRenderer* grRendererInit(grRenderer* sprite, grVec2 size);
void grSpriteRender(grSprite* sprite, grRenderer* renderer);
void grRenderSprite(grRenderer* renderer, grSprite* sprite, grQuad* quad);

#endif