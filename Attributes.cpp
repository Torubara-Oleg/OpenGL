#include "Attributes.h"

void Attributes::set_VBO(std::vector<float>& model)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, model.size() * sizeof(float), &model.front(), GL_STATIC_DRAW);
}

void Attributes::set_VAO()
{
	glBindVertexArray(this->VAO);
}

void Attributes::setAttribArrayPtr(int number, int count_of_el)
{
	//finish later...
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