#include "Model.h"

Model::Model(GLuint shader): meshes(std::vector<Mesh*>()), shaderProgram(0)
{
	shaderProgram = shader;
}

Model::~Model()
{
	if (meshes.size() > 0) {
		for (auto m : meshes) {
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}
}

void Model::Render()
{
	glUseProgram(shaderProgram);
	for (auto m : meshes) {
		m->Render();
	}
}

void Model::AddMesh(Mesh* mesh)
{
	meshes.push_back(mesh);
}
