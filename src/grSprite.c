#include "../include/grSprite.h"

grRenderer * grRendererAlloc()
{
	return malloc(sizeof(grRenderer));
}

grRenderer * grRendererInit(grRenderer * renderer)
{

	glGenVertexArrays(1, renderer->vao);
	glGenBuffers(1, &renderer->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(renderer->vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return renderer;
}

void grRendererSprite(grRenderer* renderer, grSprite* sprite)
{
	grMat4 model = grMat4Identity();
	model = grMat4Translate(model, grV4(sprite->pos.x, sprite->pos.y, 0.0, 0.0));
	model = grMat4Translate(model, grV4(0.5f * sprite->size.x, 0.5f * sprite->size.y, 0.0, 0.0));
	model = grMat4Rotate(model, grV4(0, 0, 1.0, 0), sprite->rotation);
	model = grMat4Scale(model, grV4(sprite->size.x, sprite->size.y, 1.0, 1.0));
	
	grShaderSetMat4(renderer->shader, "model", model);
	grShaderSetVec4(renderer->shader, "color", sprite->color);
	glUseProgram(renderer->shader->id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite->texture.id);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

