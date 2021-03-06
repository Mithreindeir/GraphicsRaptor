#include "../include/grSprite.h"
#include <memory.h>

const GLfloat vertices[] = {
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f
};

grQuad * grQuadAlloc()
{
	return malloc(sizeof(grQuad));
}

grQuad * grQuadInit(grQuad * quad, grVec2 pos, grVec2 size, grSprite * sprite)
{
	grVec2 tex_size = grV2(sprite->texture->width, sprite->texture->height);
	grVec2 p = grV2(0, 0);
	if (pos.x != 0)
		p.x = pos.x / tex_size.x;
	if (pos.y != 0)
		p.y = pos.y / tex_size.y;
	grVec2 s = grV2(0, 0);
	if (size.x != 0)
		s.x = size.x / tex_size.x;
	if (size.y != 0)
		s.y = size.y / tex_size.y;

	quad->vertices = malloc(sizeof(GLfloat) * 24);
	memset(quad->vertices, 0.0, sizeof(quad->vertices));
	GLfloat pvertices[] = {
		0.0f, 1.0f, p.x, p.y + s.y, // bottom left
		1.0f, 0.0f, p.x + s.x, p.y, //Top right
		0.0f, 0.0f, p.x, p.y, //Top left

		0.0f, 1.0f, p.x, p.y + s.y, // Bottom left
		1.0f, 1.0f, p.x + s.x, p.y + s.y, // bottom right
		1.0f, 0.0f, p.x + s.x, p.y // top right
	};

	memcpy(quad->vertices, pvertices, sizeof(pvertices));
	return quad;
}

grSprite * grSpriteAlloc()
{
	return malloc(sizeof(grSprite));
}

grSprite * grSpriteInit(grSprite * sprite, const char * file, int interpolate)
{
	sprite->texture = grTextureLoadFromFile(grTextureAlloc(), file, 1, interpolate);
	sprite->pos = grV2(0, 0);
	sprite->size = grV2(sprite->texture->width, sprite->texture->height);
	sprite->color = grV4(0.5, 0.5, 0.5, 1.0);
	sprite->rotation = 0;
	sprite->speed = 100;
	sprite->currentFrame = 0;
	sprite->frames = 0;
	sprite->quads = NULL;
	
	return sprite;
}

void grSpriteSetUpAnimation(grSprite * sprite, int cols, int rows)
{
	grVec2 size = grV2(sprite->size.x / cols, sprite->size.y / rows);
	sprite->size = size;
	int frames = cols*rows;
	sprite->frames = frames;
	sprite->quads = calloc(sizeof(grQuad*), frames);

	int cf = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			grVec2 pos = grV2(j*size.x, i*size.y);
			sprite->quads[cf] = grQuadInit(grQuadAlloc(), pos, size, sprite);
			cf++;
		}
	}
	
}

void grSpriteUpdate(grSprite * sprite, grFloat dt)
{
	sprite->frame_time += 1.0/dt;
	
	while (sprite->frame_time > sprite->speed && sprite->speed != 0.0)
	{
		sprite->frame_time -= sprite->speed;
		sprite->currentFrame = sprite->currentFrame < sprite->frames-1 ? sprite->currentFrame + 1 : 0;
	}
	
}


grRenderer * grRendererAlloc()
{
	return malloc(sizeof(grRenderer));
}

grRenderer * grRendererInit(grRenderer * renderer, grVec2 size)
{
	renderer->vao = 0;
	renderer->vbo = 0;
	glGenVertexArrays(1, &renderer->vao);
	glGenBuffers(1, &renderer->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindVertexArray(renderer->vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	renderer->camera = grCameraInit(grCameraAlloc(), size);
	return renderer;
}

void grSpriteRender(grSprite * sprite, grRenderer * renderer)
{
	grRenderSprite(renderer, sprite, sprite->quads[sprite->currentFrame]);
}

void grRenderSprite(grRenderer* renderer, grSprite* sprite, grQuad* quad)
{
	grShaderUse(renderer->shader);

	grMat4 model = grMat4Identity();
	grMat4 view = grCameraGetViewMatrix(renderer->camera);

	model = grMat4Translate(model, grV4(sprite->pos.x, sprite->pos.y, 0.0, 1.0));
	model = grMat4Translate(model, grV4(0.5f * sprite->size.x, 0.5f * sprite->size.y, 0.0, 1.0));
	model = grMat4Rotate(model, grV4(0, 0, 1.0, 0), sprite->rotation);
	model = grMat4Translate(model, grV4(-0.5f * sprite->size.x, -0.5f * sprite->size.y, 0.0, 1.0));
	model = grMat4Scale(model, grV4(sprite->size.x, sprite->size.y, 0.0, 1.0));
	
	grShaderSetMat4(renderer->shader, "model", model);
	grShaderSetVec4(renderer->shader, "spriteColor", sprite->color);
	grShaderSetMat4(renderer->shader, "view", view);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite->texture->id);

	glBindVertexArray(renderer->vao);
	if (quad != NULL)
	{
		GLfloat v[24];
		memcpy(v, quad->vertices, sizeof(v));
		glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	}
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

