#pragma once
#include <vector>
#include "happly.h"
#include "Attributes.h"

template<typename T>
struct AABB
{
	T min[3] = { (T)INT32_MIN,(T)INT32_MIN,(T)INT32_MIN };
	T max[3] = { (T)INT32_MAX,(T)INT32_MAX,(T)INT32_MAX };
};

class Model
{
public:
	void LoadModel(std::string filepath);
	Model()	{}
	~Model();
	Attributes model_attributes;
	AABB<float> aabb;
	std::vector<float> vertex;
	std::vector<unsigned int> index;
};
