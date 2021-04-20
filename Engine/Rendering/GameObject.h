#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
class GameObject
{
public:
	GameObject(Model* m, glm::vec3 position_ = glm::vec3(0.0f));
	~GameObject();

	void Update(const float deltaTime);
	void Render(Camera* camera);

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	float GetAngle() const;
	std::string GetID() const;
BoundingBox	GetBoundingBox() const;

	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetScale(glm::vec3 scale_);
	void SetAngle(float angle_);
	void SetID(std::string ID_);
	void SetHit(bool hit, int buttonType);

private:
	Model* model;
	unsigned int modelInstance;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float angle;
	std::string ID;
	BoundingBox boundingBox;
	bool hit;
};
#endif
