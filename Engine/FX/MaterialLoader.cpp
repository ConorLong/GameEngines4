#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(std::string filePath)
{
	std::ifstream in(filePath.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath, "LoadOBJModel.cpp", __LINE__);
		return;
	}

	Material m = Material();
	std::string matName = "";
	std::string line;

	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		
		//DIFFUSE
		if (line.substr(0, 3) == "\tKd") {
			std::stringstream n(line.substr(3));
			float x, y, z;
			n >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}
		//SPEC
		if (line.substr(0, 3) == "\tKs") {
			std::stringstream n(line.substr(3));
			float x, y, z;
			n >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}
		//AMBIENT
		if (line.substr(0, 3) == "\tKa") {
			std::stringstream n(line.substr(3));
			float x, y, z;
			n >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}
		//ALPHA
		if (line.substr(0, 2) == "\td") {
			std::stringstream n(line.substr(2));
			float x;
			n >> x;
			m.shininess = x;
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName, "./Resources/Textures/" + fileName + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName);
	}
	return currentTexture;
}
