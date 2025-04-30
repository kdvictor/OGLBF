#version 460 core

uniform vec4 ambientLightColor;
uniform vec4 ambientMaterialColor;

out vec4 FragColor;

void main()
{
	vec4 ambientColor = ambientLightColor * ambientMaterialColor;
	FragColor = ambientColor;
}