#version 460 core

layout(location = 0) in vec3 pos;

int main()
{
	gl_position = vec4(pos, 1.0);
}