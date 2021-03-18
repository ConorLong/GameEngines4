#include "Camera.h"

#include "../Core/EngineCore.h"
Camera::Camera() : position(glm::vec3()), fov(0.0f), forward(glm::vec3()), up(glm::vec3()), right(glm::vec3()), worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f), yaw(0.0f), pitch(0.0f), perspective(glm::mat4()), orthographic(glm::mat4()), view(glm::mat4()), lights(0) {
	fov = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fov, EngineCore::GetInstance()->GetScreenWidth() / EngineCore::GetInstance()->GetScreenHeight(), nearPlane, farPlane);
	orthographic = glm::ortho(0.0f, EngineCore::GetInstance()->GetScreenWidth(), 0.0f, EngineCore::GetInstance()->GetScreenHeight(), -1.0f, 1.0f);

	UpdateCameraVector();
}

Camera::~Camera()
{
	OnDestroy();
}

void Camera::SetPosition(glm::vec3 pos)
{
	position = pos;
	UpdateCameraVector();
}

void Camera::SetRotation(float yaw, float pitch)
{
	this->yaw = yaw;
	this->pitch = pitch;
	UpdateCameraVector();
}

void Camera::AddLightSource(LightSource* light)
{
	lights.emplace_back(light);
}

void Camera::OnDestroy()
{
	for (auto l : lights) {
		delete l;
		l = nullptr;
	}
	lights.clear();
}

std::vector<LightSource*> Camera::GetLightSources() const
{
	return lights;
}

glm::mat4 Camera::GetView() const
{
	return view;
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrtho() const
{
	return orthographic;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::UpdateCameraVector()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));

	view = glm::lookAt(position, position + forward, up);
}
