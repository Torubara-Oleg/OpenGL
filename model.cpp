#include "model.h"

void Model::LoadModel(std::string filepath)
{
	// Construct the data object by reading from file
	happly::PLYData plyIn(filepath);

	std::cout << "[happly]: Start reading mesh: " << filepath << std::endl;

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
		}
	}
	std::cout << "[happly]: Amount of vertices: " << vertex.size() << "\n";

	for (size_t i = 0; i < fInd.size(); i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			index.push_back(fInd[i][j]);
		}
	}

	std::cout << "[happly]: Amount of indices: " <<index.size()<< "\n";

}

Model::~Model()
{
	model_attributes.~Attributes();
	vertex.erase(vertex.begin(), vertex.end());
	index.erase(index.begin(), index.end());
}
