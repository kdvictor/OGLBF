#include <iostream>
#include "core.h"
#include "shader.h"
#include "checkError.h"
#include "application.h"


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

}

void prepareEBO()
{

}

void render()
{

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
