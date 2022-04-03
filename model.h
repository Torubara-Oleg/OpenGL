#pragma once
#include <vector>
#include "happly.h"

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

	AABB<float> aabb;
	std::vector<float> vertex;
	std::vector<unsigned int> index;
};

void Model::LoadModel(std::string filepath)
{
	// Construct the data object by reading from file
	happly::PLYData plyIn(filepath);

	std::cout << "[happly]: start reading mesh." << std::endl;
	
	// Get mesh-style data from the object
	std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
	std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices<size_t>();

	for (size_t i = 0; i < vPos.size(); i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			vertex.push_back(vPos[i][j]);
			aabb.min[j] = std::min(static_cast<float>(vPos[i][j]), aabb.min[j]);
			aabb.max[j] = std::max(static_cast<float>(vPos[i][j]), aabb.max[j]);
			//std::cout << vPos[i][j] << "\t\t\t" << vertex[i + j] << std::endl;
		}
	}
	std::cout << "[happly]: Vertex: done!" << "\n";

	for (size_t i = 0; i < fInd.size(); i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			index.push_back(fInd[i][j]);
		}
	}

	std::cout << "[happly]: Index: done!" << "\n";

}