#include "../include/grWindow.h"
#include <velocityraptor\VelocityRaptor.h>
#include "../include/grSprite.h"

grSprite* sprite;
grRenderer* renderer;
void ml(void*m);


GLchar* default_vert = "#version 330 core\n"
"layout(location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>\n"

"out vec2 TexCoords; \n"

"uniform mat4 model; \n"
"uniform mat4 projection; \n"

"void main()\n"
"{\n"
"	TexCoords = vertex.zw; \n"
"	gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0); \n"
"}\n\0";

GLchar* default_frag = "#version 330 core\n"
"in vec2 TexCoords;\n"
"out vec4 color;\n"

"uniform sampler2D image;\n"
"uniform vec4 spriteColor;\n"

"void main()\n"
"{\n"
"	color = vec4(spriteColor) * texture(image, TexCoords);\n"
"}\n\0";

int
main(void)
{
	grMat4 p = grMat4Identity();
	p = grMat4Rotate(p, grV4(0, 0, 1, 0), 45.0);
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f  ", p.m[i].v[j]);
		printf("\n");
	}
	grInit();
	grWindow* wind = grWindowInit(grWindowAlloc(), 640, 640);
	wind->userFunc = &ml;
	grShader* default_shader = grShaderInit(grShaderAlloc());
	grShaderCompile(default_shader, default_vert, default_frag);
	renderer = grRendererInit(grRendererAlloc());
	sprite = grSpriteInit(grSpriteAlloc(), "awesomeface.png");
	sprite->pos = grV2(0, 0);
	grMat4 proj = grOrtho(0.0, 640.0, 0.0, 640.0);

	renderer->shader = default_shader;
	grShaderUse(renderer->shader);
	grShaderSetInteger(renderer->shader, "image", 0);
	grShaderSetMat4(renderer->shader, "projection", proj);
	grMainLoop(wind);
	grDestroy(wind);
	return 1;
}
void ml(void*m)
{
	grRendererSprite(renderer, sprite);
}
