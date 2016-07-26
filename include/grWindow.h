
#ifndef HEADER_GRWINDOW
#define HEADER_GRWINDOW
#include "graphicsraptor.h"


int keys[1024];
typedef void*(*grKeyPressedFunc)(int key);
typedef void*(*grKeyReleasedFunc)(int key);
grKeyPressedFunc keypressed;
grKeyReleasedFunc keyreleased;
typedef void*(*grMainLoopUserFunc)(void* userdata);
typedef struct grWindow
{
	GLFWwindow* window;

	int width;
	int height;
	int avg_fps;
	int frames;
	grMainLoopUserFunc userFunc;
	void* userData;
} grWindow;
void grInit();
void grDestroy(grWindow* window);
grWindow* grWindowAlloc();
grWindow* grWindowInit(grWindow* window, int width, int height);
void default_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void grMainLoop(grWindow* window);

#endif