#include "../init.h"

#include <iostream>
using namespace std;


int main(int argc, char const *argv[])
{
	Init();

    // Create window
    GLFWwindow_unique_ptr window = CreateGlWindow(640, 480, "0 - Hello, GLFW!", nullptr, nullptr);

	gl::ClearColor(1.0, 0.7, 0.0, 1.0);

	//Main loop
	while(!glfwWindowShouldClose(window.get()))
	{
		glfwPollEvents(); //Here event callbacks get fired

		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window.get());
	}

	return 0;
}
