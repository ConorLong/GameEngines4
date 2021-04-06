#include "LoadOBJModel.h"
LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), texCoords(std::vector<glm::vec2>()), indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()), meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentMaterial(Material()) 
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
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
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
				
			for (int i = 0; i < s.size() - 1; i++) {
				int t = i + 1;
				if (!isspace(s[i + 1])) {
					if (isdigit(s.at(i)) && isdigit(s.at(i + 1))) {
					}
					else {
						if (!isspace(s[i + 1])) {
							s.insert(i + 1, " ");
							++i;
						}
					}
				}
			}
			s.erase(remove(s.begin(), s.end(), '/'), s.end());
			std::stringstream f(s);
			
			int index[3], tex[3], norm[3];
			
			f >> index[0] >> tex[0] >> norm[0]
				>> index[1] >> tex[1] >> norm[1]
				>> index[2] >> tex[2] >> norm[2];

			for (int i = 0; i < 3; i++) {
				int ctr = 0;
				indices.push_back(index[i] - 1);
				textureIndices.push_back(tex[i] - 1);
				normalIndices.push_back(norm[i] - 1);
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
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName);
	
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath)
{
	MaterialLoader::LoadMaterial(matFilePath);
}
