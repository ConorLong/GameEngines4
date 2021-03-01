#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
class Model
{
public:
	Model(GLuint shaderProgram, glm::vec3 pos = glm::vec3(), 
									float angle = 0.0f, 
								glm::vec3 rot = glm::vec3(0.0f, 1.0f, 0.0f),
								glm::vec3 scale = glm::vec3(1.0f));
	~Model();

	void Render(Camera* camera);
	void AddMesh(Mesh* mesh);

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	float GetAngle() const;
	glm::mat4 GetTransform() const;

	void SetPosition( glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetScale(glm::vec3 scale_);
	void SetAngle(float angle_);

private:
	std::vector<Mesh*> meshes;
	GLuint shaderProgram;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float angle;
};
#endif
