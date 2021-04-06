#include "GameObject.h"

GameObject::GameObject(Model* m) : model(nullptr), position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)), modelInstance(0)
{
	model = m;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}

}

GameObject::GameObject(Model* m, glm::vec3 position_) : model(nullptr), position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)), modelInstance(0)
{
	model = m;
	position = position_;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
}

GameObject::~GameObject()
{
	model = nullptr;
}

void GameObject::Update(const float deltaTime)
{
	SetAngle(angle + 0.005f);
}

void GameObject::Render(Camera* camera)
{
	if (model) {
		model->Render(camera);
	}
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

float GameObject::GetAngle() const
{
	return angle;
}

std::string GameObject::GetID() const
{
	return ID;
}

void GameObject::SetPosition(glm::vec3 pos)
{
	position = pos;
	if (model != nullptr) {
		 model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetRotation(glm::vec3 rot)
{
	rotation = rot;
	if (model != nullptr) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model != nullptr) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model != nullptr) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetID(std::string ID_)
{
	ID = ID_;
}
