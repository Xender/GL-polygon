#ifndef INIT_H
#define INIT_H

#include "../gl_3_3_core.hpp"
#include <GLFW/glfw3.h>

#include <memory>

// unique_ptr specialization
struct GlfwWindowDeleter
{
	void operator()(GLFWwindow* window)
	{
		glfwDestroyWindow(window); //TODO - can nullptr be safely passed?
	}
};
typedef std::unique_ptr<GLFWwindow, GlfwWindowDeleter> GLFWwindow_unique_ptr;

GLFWwindow_unique_ptr CreateGlWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
void Init();

#endif // INIT_H
