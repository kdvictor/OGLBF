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
const char* const DIFFUSE_VS = R"(#version 460 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 NM;

out vec3 normal;

void main()
{
	normal =  mat3(NM) * inNormal;
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
const char* const DIFFUSE_FS = R"(#version 460 core

uniform vec3 lightPos;
uniform float ambientStrength;
uniform vec4 lightColor;
uniform vec4 objColor;

in vec3 normal;

out vec4 FragColor;

void main()
{
	vec4 ambientLightColor = ambientStrength * lightColor;

	//diffuse
	vec3 lightDirection = normalize(lightPos);
	vec3 normalDirection = normalize(normal);
	float diffuseStrength = clamp(dot(lightDirection,normalDirection),0.0,1.0) * 0.8;
	vec4 diffuseColor = diffuseStrength * lightColor;

	FragColor = (ambientLightColor + diffuseColor) * objColor;
})";
