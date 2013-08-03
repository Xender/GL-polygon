#include "init.h"

#include <iostream>
using namespace std;

GLFWwindow_unique_ptr CreateGlWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    //Create GLFW window with OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow_unique_ptr window(
		glfwCreateWindow(width, height, title, monitor, share));
    if(!window)
    {
		cerr << "Error - Failed to open GLFW window";
		return nullptr;
    }

    glfwMakeContextCurrent(window.get());

    //Load GL
	gl::exts::LoadTest load_result = gl::sys::LoadFunctions();
	int num_missing = load_result.GetNumMissing();
	if(!load_result)
	{
		cerr << "Error - Failed to load OpenGL entirely" << endl;
		return nullptr;
	}
	if(num_missing)
		cerr << "Warning - Failed to load " << std::to_string(num_missing) << " OpenGL functions" << endl;

	return window;
}

void Init()
{
	// This function can be called before glfwInit
	glfwSetErrorCallback(
		[](int id, const char* description)
		{
			cerr << "GLFW Error - " << std::to_string(id) << ": " << description << endl;
		});

	// Initialize GLFW
	if(!glfwInit())
	{
		cerr << "Fatal - glfwInit() failed" << endl;
		exit(1);
	}
	atexit(glfwTerminate);
}
