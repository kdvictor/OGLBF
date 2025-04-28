#pragma once

//vs
const char* const AMBIENT_VS = R"(#version 460 core

layout(location = 0) in vec3 pos;

int main()
{
	gl_position = vec4(pos, 1.0);
})";

//fs
const char* const AMBIENT_FS = R"(#version 460 core

out vec4 FragColor;

int main()
{
	FragColor = vec4(1.0,0.0,0.0,1.0);
})";
