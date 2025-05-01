#pragma once

//vs
const char* const AMBIENT_VS = R"(#version 460 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
//uniform mat4 NM;

//out vec3 outNormal;

void main()
{
	gl_Position = P * V * M * vec4(inPos, 1.0);
})";

//fs
const char* const AMBIENT_FS = R"(#version 460 core

uniform float ambientStrength;
uniform vec4 lightColor;
uniform vec4 objColor;

out vec4 FragColor;

void main()
{
	vec4 ambientLightColor = ambientStrength * lightColor;
	vec4 ambientColor = ambientLightColor * objColor;
	FragColor = ambientColor;
})";
