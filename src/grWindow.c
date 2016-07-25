#include "../include/grWindow.h"

void grInit()
{
	keypressed = NULL;
	keyreleased = NULL;
	glfwInit();

}

void grDestroy(grWindow * window)
{
	glfwDestroyWindow(window->window);
	free(window);
	glfwTerminate();
}

grWindow * grWindowAlloc()
{
	return malloc(sizeof(grWindow));
}

grWindow * grWindowInit(grWindow * window, int width, int height)
{
	window->width = width;
	window->height = height;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	window->window = glfwCreateWindow(width, height, "Graphics Raptor", NULL, NULL);
	glfwMakeContextCurrent(window->window);
	glewExperimental = GL_TRUE;
	glewInit();

	glfwSwapInterval(1);
	glfwSetKeyCallback(window, default_key_callback);
	window->userData = NULL;
	window->userFunc = NULL;
	return window;

}

void default_key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
	{
		keys[key] = 1;
		if(keypressed) keypressed(key);
	}

	if (action == GLFW_RELEASE)
	{
		keys[key] = 0;
		if(keyreleased) keyreleased(key);
	}
}

void grMainLoop(grWindow * window)
{
	while (!glfwWindowShouldClose(window->window))
	{
		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		if (window->userFunc)
			window->userFunc(window->userData);

		glfwSwapBuffers(window->window);
		glfwPollEvents();

	}
}
