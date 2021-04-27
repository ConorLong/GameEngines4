#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<vector>

#include "../FX/LightSource.h"

class Frustum;
class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 pos);
	void SetRotation(float yaw, float pitch);

	void AddLightSource(LightSource* light);

	void OnDestroy();
	std::vector<LightSource*> GetLightSources() const;

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrtho() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetForward() const;
	glm::vec3 GetUp() const;
	glm::vec3 GetRight() const;
	Frustum GetFrustum() const;

	float GetFOV() const;
	float GetNearPlane() const;
	float GetFarPlane() const;

	void ProcessMouseMovement(glm::vec2 offset);
	void ProcessMouseZoom(int y);

private:


	Frustum* frustum;
	void UpdateCameraVector();

	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fov;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	std::vector<LightSource*> lights;
};
#endif
