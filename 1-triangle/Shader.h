#ifndef SHADER_H
#define SHADER_H

#include "../gl_3_3_core.hpp"

#include <utility>

class Shader
{
public:
	class Subprogram;

	Shader()
		:id (gl::CreateProgram())
	{}

	~Shader()
	{
		gl::DeleteProgram(id); //0 is silently ignored.
	}

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& rhs)
		: id(rhs.id)
	{
		rhs.id = 0;
	}

	Shader& operator=(Shader&& rhs)
	{
		std::swap(id, rhs.id);
		return *this;
	}

	/*GLuint GetId()
	{
		return id;
	}*/

	void AddSubprogram(const Subprogram& s)
	{
		gl::AttachShader(id, s.id);
	}

	void RemoveSubprogram(const Subprogram& s)
	{
		gl::DetachShader(id, s.id);
	}

	bool Link();

	void Use()
	{
		gl::UseProgram(id);
	}

private:
	GLuint id;

public:
	class Subprogram
	{
	friend class Shader;
	public:
		Subprogram(GLenum type)
			: id( gl::CreateShader(type))
		{}

		~Subprogram()
		{
			gl::DeleteShader(id); //0 will be silently ignored.
		}

		Subprogram(const Subprogram&) = delete;
		Subprogram& operator=(const Subprogram&) = delete;

		Subprogram(Subprogram&& rhs)
			: id(rhs.id)
		{
			rhs.id = 0;
		}

		Subprogram& operator=(Subprogram&& rhs)
		{
			std::swap(id, rhs.id);
			return *this;
		}

		bool LoadSource(const char* sources[], GLsizei count);

	private:
		GLuint id;
	};
};

#endif // SHADER_H
