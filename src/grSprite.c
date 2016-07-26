#include "../include/grSprite.h"

grSprite * grSpriteAlloc()
{
	return malloc(sizeof(grSprite));
}

grSprite * grSpriteInit(grSprite * sprite, const char * file)
{
	sprite->texture = grTextureLoadFromFile(grTextureAlloc(), file, 1);
	sprite->pos = grV2(0, 0);
	sprite->size = grV2(sprite->texture->width, sprite->texture->height);
	sprite->color = grV4(0.5, 0.5, 0.5, 1);
	sprite->rotation = 0;

	return sprite;
}

grRenderer * grRendererAlloc()
{
	return malloc(sizeof(grRenderer));
}

grRenderer * grRendererInit(grRenderer * renderer)
{
	renderer->vao = 0;
	renderer->vbo = 0;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &renderer->vao);
	glGenBuffers(1, &renderer->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(renderer->vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return renderer;
}

void grRendererSprite(grRenderer* renderer, grSprite* sprite)
{
	grShaderUse(renderer->shader);

	grMat4 model = grMat4Identity();
	model = grMat4Translate(model, grV4(sprite->pos.x, sprite->pos.y, 0.0, 1.0));
	model = grMat4Translate(model, grV4(0.5f * sprite->size.x, 0.5f * sprite->size.y, 0.0, 0.0));
	model = grMat4Rotate(model, grV4(0, 0, 1.0, 0), sprite->rotation);
	model = grMat4Translate(model, grV4(-0.5f * sprite->size.x, -0.5f * sprite->size.y, 0.0, 0.0));

	model = grMat4Scale(model, grV4(sprite->size.x, sprite->size.y, 1.0, 0.0));
	
	grShaderSetMat4(renderer->shader, "model", model);
	grShaderSetVec4(renderer->shader, "spriteColor", sprite->color);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite->texture->id);

	glBindVertexArray(renderer->vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

