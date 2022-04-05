#pragma once
#include <glad/glad.h>
#include <vector>

class Attributes
{
public:
	void set_EBO(std::vector<unsigned int>& index);
	void set_VBO(std::vector<float>& model);
	void set_VAO();
	void setAttribArrayPtr(int number, int count_of_el);
	unsigned int get_VAO();
	~Attributes();
	Attributes();
protected:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
};