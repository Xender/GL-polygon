#include "Shader.h"

#include <vector>
#include <iostream>
using namespace std;

bool Shader::Link()
{
	gl::LinkProgram(id);

	//Check
	GLint link_status;
	gl::GetProgramiv(id, gl::LINK_STATUS, &link_status);

	GLint info_log_length;
	gl::GetProgramiv(id, gl::INFO_LOG_LENGTH, &info_log_length);

	if(info_log_length <= 1) //One character long info log consists of only null terminator.
	{
		if(link_status)
			cerr << "Info - Shader program linked successfully." << endl;
		else
			cerr << "Error - Error while linking shader program. No further information available. :(" << endl;
	}
	else
	{
		std::vector<GLchar> info_log(info_log_length);
		gl::GetProgramInfoLog(id, info_log_length, nullptr, info_log.data());

		if(link_status)
			cerr << "Warning - " << info_log.data() << endl;
		else
			cerr << "Error - " << info_log.data() << endl;
	}

	return link_status;
}

bool Shader::Subprogram::LoadSource(const char* sources[], GLsizei count)
{
	//Compile
	GLint compile_status;
	gl::ShaderSource(id, count, sources, nullptr);
	gl::CompileShader(id);

	//Check
	gl::GetShaderiv(id, gl::COMPILE_STATUS, &compile_status);

	GLint info_log_length;
	gl::GetShaderiv(id, gl::INFO_LOG_LENGTH, &info_log_length);

	if(info_log_length <= 1) //One character long info log consists of only null terminator.
	{
		if(compile_status)
			cerr << "Info - Shader compiled successfully." << endl;
		else
			cerr << "Error - Error while compiling shader. No further information available. :(" << endl;
	}
	else
	{
		std::vector<GLchar> info_log(info_log_length);
		gl::GetShaderInfoLog(id, info_log_length, nullptr, info_log.data());

		if(compile_status)
			cerr << "Warning - " << info_log.data() << endl;
		else
			cerr << "Error - " << info_log.data() << endl;
	}

	return compile_status;
}
