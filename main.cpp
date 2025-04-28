#include <iostream>
#include <vector>
#include "core.h"
#include "shader.h"
#include "checkError.h"
#include "application.h"
#include "program.h"
#include "glm/mat4x4.hpp"
#include "glm/common.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

GLuint vao;
Program* program;
int elementNum = 0;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void OnKeyChange(const int& key, const int& action, const int& mods)
{
	//GLFW_PRESS,GLFW_RELEASE,GLFW_MOD_CONTROL,GLFW_MOD_SHIFT
	if (key == GLFW_KEY_W)
	{
		std::cout << "key: " << key << std::endl;
		std::cout << "action: " << action << std::endl;
		std::cout << "mods: " << mods << std::endl;
	}
}


void onResize(const int& width, const int& height)
{
	GL_CALL(glViewport(0, 0, width, height));
	std::cout << "onResize" << std::endl;
}

void buildProgram()
{
	program = new Program();
	program->attachShader(VERTEX, AMBIENT_VS);
	program->attachShader(FRAGMENT, AMBIENT_FS);
	program->build();
}

// 修改后的顶点数据生成函数（新增法线数据）
void generateSphere(std::vector<float>& vertices, std::vector<unsigned int>& indices, int stacks = 36, int slices = 36) {
	const float PI = 3.1415926535f;

	for (int i = 0; i <= stacks; ++i) {
		float phi = i * PI / stacks;  // 极角（从上到下）

		for (int j = 0; j <= slices; ++j) {
			float theta = j * 2 * PI / slices;  // 方位角（绕Z轴旋转）

			// 正确球面坐标公式
			float x = sin(phi) * cos(theta);
			float y = sin(phi) * sin(theta);
			float z = cos(phi);

			// 顶点位置（同时作为法线）
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}
	}

	// 索引生成保持不变
	for (int i = 0; i < stacks; ++i) {
		int current = i * (slices + 1);
		int next = (i + 1) * (slices + 1);

		for (int j = 0; j < slices; ++j) {
			indices.push_back(current + j);
			indices.push_back(next + j);
			indices.push_back(current + j + 1);

			indices.push_back(next + j);
			indices.push_back(next + j + 1);
			indices.push_back(current + j + 1);
		}
	}
}
void prepareEBO()
{
	//generate sphere data
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	generateSphere(vertices, indices);
	elementNum = indices.size();

	//vertex vbo
	GLuint vetexVbo;
	GL_CALL(glGenBuffers(1, &vetexVbo));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vetexVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));

	//ebo
	GLuint vertexEbo;
	GL_CALL(glGenBuffers(1, &vertexEbo));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexEbo));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));

	//vao
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));

	//description
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vetexVbo));
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));

	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float))));

	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexEbo));//open ebo and bind to current vao

	GL_CALL(glBindVertexArray(0));
}

void render()
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	program->start();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	program->setUniformMatrix4fv("M", model);
	program->setUniformMatrix4fv("V", view);
	program->setUniformMatrix4fv("P", projection);

	//bind vao
	GL_CALL(glBindVertexArray(vao));

	//render
	GL_CALL(glDrawElements(GL_TRIANGLES, elementNum, GL_UNSIGNED_INT, (void*)0));

	program->end();
}

int main()
{
	_app.init(800.600);
	
	//listen events
	_app.setResizeCallback(onResize);
	_app.setKeyCallback(OnKeyChange);

	//build program
	buildProgram();

	//prepare ebo
	prepareEBO();

	//texture

	//set viewport and color
	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.0, 0.0, 0.0, 1.0));

	//loop
	while (_app.update())
	{
		render();
	}

	_app.destory();

	return 0;
}
