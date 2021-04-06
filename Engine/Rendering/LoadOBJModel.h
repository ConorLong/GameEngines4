#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include<sstream>
#include <cctype>
#include "Mesh.h"
#include "../Graphics/TextureHandler.h"
#include "../FX/MaterialLoader.h"

class LoadOBJModel
{
	public:
	LoadOBJModel();
	~LoadOBJModel();

	void LoadModel(const std::string& objFilePath, const std::string& mtlFilePath);
	std::vector<SubMesh> GetSubMeshes();

private:
	void PostProcessing();
	void LoadModel(const std::string& filePath);
	void LoadMaterial(const std::string& matName);
	void LoadMaterialLibrary(const std::string& matFilePath);


	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices, normalIndices, textureIndices;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> subMeshes;

	Material currentMaterial;
};
#endif
