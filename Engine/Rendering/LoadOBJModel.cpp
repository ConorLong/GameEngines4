#include "LoadOBJModel.h"
LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), texCoords(std::vector<glm::vec2>()), indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()), meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentTexture(0) 
{
	vertices.reserve(200);
	normals.reserve(200);
	texCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200); 
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel() {
	vertices.clear();
	normals.clear();
	texCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath, const std::string& mtlFilePath)
{
	LoadMaterialLibrary(mtlFilePath);
	LoadModel(objFilePath);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = texCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.textureID = currentTexture;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentTexture = 0;
}

void LoadOBJModel::LoadModel(const std::string& filePath)
{
	std::ifstream in(filePath.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath, "LoadOBJModel.cpp", __LINE__);
		return;
	}

	std::string line;
	while (std::getline(in, line)) {
		//VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}
		//NORMALS
		if (line.substr(0, 3) == "vn ") {
			std::stringstream n(line.substr(2));
			float x, y, z;
			n >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		//TEXTURES
		if (line.substr(0, 3) == "vt ") {
			std::stringstream t(line.substr(2));
			float x, y, z;	
			texCoords.push_back(glm::vec2(x, y));
		}
		//FACE
		if (line.substr(0, 2) == "f ") {
			std::stringstream faces(line.substr(2));
			std::string s = faces.str();
			s.erase(remove(s.begin(), s.end(), '/'), s.end());
			
			std::stringstream f(s);
			
			unsigned int index[3], tex[3], norm[3];
			

			for (int i = 0; i < 3; i++) {
				int ctr = 0;
				indices.push_back(index[0] - 1);
				textureIndices.push_back(tex[0] - 1);
				normalIndices.push_back(norm[0] - 1);
				ctr += 5;
			}
		}
		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName)
{
	currentTexture = TextureHandler::GetInstance()->GetTexture(matName);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(matName, "Resources/Textures" + matName + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(matName);
	}
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath)
{
	std::ifstream in(matFilePath.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + matFilePath, "LoadOBJModel.cpp", __LINE__);

	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			LoadMaterial(line.substr(7));
		}
	}
}
