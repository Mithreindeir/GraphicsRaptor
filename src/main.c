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
"uniform mat4 view; \n"

"void main()\n"
"{\n"
"	TexCoords = vertex.zw; \n"
"	gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0); \n"
"}\n\0";

GLchar* default_frag = "#version 330 core\n"
"in vec2 TexCoords;\n"
"out vec4 color;\n"

"uniform sampler2D image;\n"
"uniform vec4 spriteColor;\n"

"void main()\n"
"{\n"
"	color = spriteColor * texture(image, TexCoords);\n"
"}\n\0";

int
main(void)
{

	grInit();
	grWindow* wind = grWindowInit(grWindowAlloc(), 1024, 1024);
	wind->userFunc = &ml;
	grShader* default_shader = grShaderInit(grShaderAlloc());
	grShaderCompile(default_shader, default_vert, default_frag);
	renderer = grRendererInit(grRendererAlloc(), grV2(1024, 1024));
	sprite = grSpriteInit(grSpriteAlloc(), "player_run.png", 0);
	grSpriteSetUpAnimation(sprite, 8, 1);
	sprite->speed = 300;
	sprite->size = grVec2Scale(sprite->size, 8.0);
	sprite->pos = grV2(400, 400);
	//renderer->camera->zoom.zoomTarget = 2;
	//quad = grQuadInit(grQuadAlloc(), grV2(4*64, 0), grV2(64, 64), sprite);
	grMat4 proj = grCameraGetProjectionMatrix(renderer->camera);
	renderer->shader = default_shader;
	grShaderUse(renderer->shader);
	grShaderSetInteger(renderer->shader, "image", 0);
	grShaderSetMat4(renderer->shader, "projection", proj);
	grMainLoop(wind);
	grDestroy(wind);
	return 1;
}
vrFloat ct;
vrFloat lt = 0;
void ml(void*m)
{
	ct = glfwGetTime();
	vrFloat dt = ct - lt;
	grCameraUpdate(renderer->camera, dt);
	grSpriteUpdate(sprite, dt);
	grSpriteRender(sprite, renderer);
	//grRenderSprite(renderer, sprite, NULL);
	grShaderUse(renderer->shader);
	grMat4 proj = grCameraGetProjectionMatrix(renderer->camera);
	grShaderSetMat4(renderer->shader, "projection", proj);
	lt = ct;
}
