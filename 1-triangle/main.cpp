#include "../init.h"
#include "Shader.h"
#include "misc.h"
#include <string>

#include <iostream>
using namespace std;

Shader::Subprogram LoadSubprogramFromFile(GLenum type, const char* filename)
{
	Shader::Subprogram s(type);
	std::vector<char> source = ReadFile(filename, true);
	if(source.empty())
		return s;

	const char * data = source.data();
	s.LoadSource(&data, 1);
	return s;
}

Shader LoadShaderFromFiles(const std::string& filename_base)
{
	Shader s;

	Shader::Subprogram vert = LoadSubprogramFromFile(gl::VERTEX_SHADER, (filename_base + ".vert").c_str());
	Shader::Subprogram frag = LoadSubprogramFromFile(gl::FRAGMENT_SHADER, (filename_base + ".frag").c_str());

	s.AddSubprogram(vert);
	s.AddSubprogram(frag);

	s.Link();

	s.RemoveSubprogram(vert);
	s.RemoveSubprogram(frag);

	return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// helper to check and display for shader compiler errors
bool check_shader_compile_status(GLuint obj)
{
    GLint status;
    gl::GetShaderiv(obj, gl::COMPILE_STATUS, &status);
    if(status == gl::FALSE_)
    {
        GLint length;
        gl::GetShaderiv(obj, gl::INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        gl::GetShaderInfoLog(obj, length, &length, &log[0]);
        std::cerr << &log[0];
        return false;
    }
    return true;
}

// helper to check and display for shader linker error
bool check_program_link_status(GLuint obj)
{
    GLint status;
    gl::GetProgramiv(obj, gl::LINK_STATUS, &status);
    if(status == gl::FALSE_)
    {
        GLint length;
        gl::GetProgramiv(obj, gl::INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        gl::GetProgramInfoLog(obj, length, &length, &log[0]);
        std::cerr << &log[0];
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	Init();

    // Create window
    GLFWwindow_unique_ptr window = CreateGlWindow(640, 480, "1 - First triangle", nullptr, nullptr);

	struct Vertex
	{
		float position[3];
		float color[3];
	};

	GLuint vbo;
	gl::GenBuffers(1, &vbo);

	// Batch
	const size_t vertex_count = 3;

	Vertex vertices[vertex_count] =
	{
		{{-0.7f, -0.7f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{-0.7f,  0.7f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 0.7f, -0.7f, 0.0f}, {0.0f, 0.0f, 1.0f}}
	};

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(vertices), vertices, gl::STATIC_DRAW);

	// Setup VAO
	GLuint vao;
	gl::GenVertexArrays(1, &vao);
	gl::BindVertexArray(vao);

	//gl::BindBuffer(gl::ARRAY_BUFFER, vbo); - VBO is already bound, so we can skip this

	gl::EnableVertexAttribArray(0);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, false, sizeof(Vertex), static_cast<char*>(nullptr)+offsetof(Vertex, position));

	gl::EnableVertexAttribArray(1);
	gl::VertexAttribPointer(1, 3, gl::FLOAT, false, sizeof(Vertex), static_cast<char*>(nullptr)+offsetof(Vertex, color));

	// Setup shader
	Shader s = LoadShaderFromFiles("flat");
	s.Use();

	// Draw
	gl::ClearColor(1.0, 0.7, 0.0, 1.0);

	// Main loop
	while(!glfwWindowShouldClose(window.get()))
	{
		glfwPollEvents(); //Here event callbacks get fired

		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

		s.Use();
		gl::BindVertexArray(vao);
		gl::DrawArrays(gl::TRIANGLES, 0, 3);

		GLenum error;
        while((error = gl::GetError()) != gl::NO_ERROR_)
        {
            std::cerr << error << endl;
        }

		glfwSwapBuffers(window.get());
	}

	// Why we need RAII for VAOs and ABOs, like for shaders
	gl::DeleteVertexArrays(1, &vao);
    gl::DeleteBuffers(1, &vbo);

	return 0;
}
