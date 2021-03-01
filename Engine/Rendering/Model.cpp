#include "Model.h"

Model::Model(GLuint shader,	glm::vec3 pos,
								float angle,
							glm::vec3 rot,
							glm::vec3 scale_)
							: meshes(std::vector<Mesh*>()), shaderProgram(0), position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f))
{
	shaderProgram = shader;
	position = pos;
	rotation = rot;
	scale = scale_;
	this->angle = angle;
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
	glUseProgram(shaderProgram);
	for (auto m : meshes) {
		m->Render(camera, GetTransform());
	}
}

void Model::AddMesh(Mesh* mesh)
{
	meshes.push_back(mesh);
}

glm::vec3 Model::GetPosition() const
{
	return position;
}

glm::vec3 Model::GetRotation() const
{
	return rotation;
}

glm::vec3 Model::GetScale() const
{
	return scale;
}

float Model::GetAngle() const
{
	return angle;
}

glm::mat4 Model::GetTransform() const
{
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, rotation);
	model = glm::scale(model, scale);
	return model;
}

void Model::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void Model::SetRotation(glm::vec3 rot) 
{
	rotation = rot;
}

void Model::SetScale(glm::vec3 scale_) 
{
	scale = scale_;
}

void Model::SetAngle(float angle_)
{
	angle = angle_;
}
