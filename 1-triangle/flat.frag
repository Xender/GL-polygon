#version 330 core

in vec3 interp_color;

layout (location = 0) out vec4 frag_color;

void main()
{
	frag_color = vec4(interp_color, 1.0);
}
