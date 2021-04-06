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
		else if (line.substr(0, 2) == "") {}
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
