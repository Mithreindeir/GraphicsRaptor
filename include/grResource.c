#include "grResource.h"

grTexture * grTextureAlloc()
{
	return malloc(sizeof(grTexture));
}

grTexture * grTextureInit(grTexture * texture, GLuint w, GLuint h, unsigned char * dat)
{
	glGenTextures(1, &texture->id);
	texture->width = w;
	texture->height = h;

	glBindTexture(GL_TEXTURE_2D, texture->id);
	glTexImage2D(GL_TEXTURE_2D, 0, texture->internal_f, w, h, 0, texture->image_f, GL_UNSIGNED_BYTE, dat);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

grTexture * grTextureLoadFromFile(grTexture * texture, const char * file, int alpha)
{
	if (alpha)
	{
		texture->image_f = GL_RGBA;
		texture->internal_f = GL_RGBA;
	}
	else
	{
		texture->image_f = GL_RGB;
		texture->internal_f = GL_RGB;
	}
	int w, h;
	unsigned char* image = SOIL_load_image(file, &w, &h, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	texture = grTextureInit(texture, w, h, image);
	SOIL_free_image_data(image);
	return texture;
}

grShader * grShaderAlloc()
{
	return malloc(sizeof(grShader));
}

grShader * grShaderInit(grShader * shader)
{
	shader->id = -1;
	
	return shader;
}

void grShaderCompile(grShader * shader, const GLchar * vs, const GLchar * fs)
{
	GLuint v, f;
	v = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v, 1, &vs, NULL);
	glCompileShader(v);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f, 1, &fs, NULL);
	glCompileShader(f);
	shader->id = glCreateProgram();
	glAttachShader(shader->id, v);
	glAttachShader(shader->id, f);
	glLinkProgram(shader->id);
	glDeleteShader(v);
	glDeleteShader(f);
}

void grShaderSetFloat(grShader * shader, const GLchar * name, GLfloat f)
{
	glUniform1f(glGetUniformLocation(shader->id, name), f);
}

void grShaderSetInteger(grShader * shader, const GLchar * name, GLint i)
{
	glUniform1i(glGetUniformLocation(shader->id, name), i);
}

void grShaderSetVec4(grShader * shader, const GLchar * name, grVec4 v)
{
	glUniform4f(glGetUniformLocation(shader->id, name), v.x, v.y, v.z, v.w);
}

void grShaderSetMat4(grShader * shader, const GLchar * name, grMat4 m)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, grMat4Ptr(m));
}