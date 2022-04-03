#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "KHR/khrplatform.h"
#include <iostream>
#include <vector>

void init_window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* create_window(int SCR_WIDTH, int SCR_HEIGHT, const char* name)
{
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name, NULL, NULL);	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	return window;
}

// ќбработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующа€ обработка данных событий
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: вс€кий раз, когда измен€ютс€ размеры окна (пользователем или операционной системой), вызываетс€ данна€ callback-функци€
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ”беждаемс€, что окно просмотра соответствует новым размерам окна. 
	// ќбратите внимание, высота окна на Retina-диспле€х будет значительно больше, чем указано в программе
	glViewport(0, 0, width, height);
}

int loadGlad()
{
	// glad: загрузка всех указателей на OpenGL-функции
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}


class Attributes
{
public:
	void set_EBO(std::vector<unsigned int>& index);
	void set_VBO(std::vector<float>& model);
	unsigned int get_VAO();
	~Attributes();
	Attributes();
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
};

void Attributes::set_VBO(std::vector<float> &model)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, model.size() * sizeof(float), &model.front(), GL_STATIC_DRAW);
}

void Attributes::set_EBO(std::vector<unsigned int>& index)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), &index.front(), GL_STATIC_DRAW);
}

Attributes::~Attributes()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

Attributes::Attributes()
{
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	glGenVertexArrays(1, &this->VAO);
}

unsigned int Attributes::get_VAO()
{
	return this->VAO;
}

void Hello()
{
	std::cout << "Hello" << std::endl;
}