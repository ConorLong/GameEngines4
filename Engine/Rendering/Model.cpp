#include "Model.h"


Model::Model(GLuint shaderProgram_, const std::string& objPath, const std::string matPath): meshes(std::vector<Mesh*>()), shaderProgram(0), modelInstances(std::vector<glm::mat4>())
{
	shaderProgram = shaderProgram_;
	meshes.reserve(10);
	modelInstances.reserve(5);
	obj = new LoadOBJModel();
	obj->LoadModel(objPath, matPath);
	LoadModel();
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

void Model::Render(Camera* camera)
{
	//if (camera->frustum.CheckBox(boundingBox)) {
		glUseProgram(shaderProgram);
		for (auto m : meshes) {
			m->Render(camera, modelInstances);
		}
	
	//}
//	else {
	//	std::cout << "NOT RENDERED" << std::endl;
	//}

}

void Model::AddMesh(Mesh* mesh)
{
	meshes.push_back(mesh);
}

unsigned int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances.push_back(CreateTransform(position_, angle_, rotation_, scale_));
	return modelInstances.size() - 1;
}

void Model::UpdateInstance(unsigned int index, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances[index] = CreateTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(unsigned int index) const
{
	return modelInstances[index];
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

BoundingBox Model::GetBoundingBox() const
{
	return boundingBox;
}

glm::mat4 Model::CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_ , rotation_);
	model = glm::scale(model, scale_);
	return model;
}

void Model::LoadModel()
{
	for (int i = 0; i < obj->GetSubMeshes().size(); i++) {
		meshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}

	boundingBox = obj->GetBoundingBox();
	delete obj;
	obj = nullptr;
}

