#include "Camera.h"

#include "Frustum.h"
#include "../Core/EngineCore.h"

Camera::Camera() : position(glm::vec3()), fov(0.0f), forward(glm::vec3()), up(glm::vec3()), right(glm::vec3()), worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f), yaw(0.0f), pitch(0.0f), perspective(glm::mat4()), orthographic(glm::mat4()), view(glm::mat4()), lights(0) {
	fov = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 100.0f;
	yaw = -90.0f;
	pitch = 0.0f;
	
	perspective = glm::perspective(fov, EngineCore::GetInstance()->GetScreenWidth() / EngineCore::GetInstance()->GetScreenHeight(), nearPlane, farPlane);
	orthographic = glm::ortho(0.0f, EngineCore::GetInstance()->GetScreenWidth(), 0.0f, EngineCore::GetInstance()->GetScreenHeight(), -1.0f, 1.0f);


	frustum = new Frustum();
	frustum->CalculateFrustum(this);
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
	frustum->CalculateFrustum(this);
}

void Camera::SetRotation(float yaw, float pitch)
{
	this->yaw = yaw;
	this->pitch = pitch;
	UpdateCameraVector();
	frustum->CalculateFrustum(this);
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
	delete frustum;
	frustum = nullptr;
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

glm::vec3 Camera::GetForward() const
{
	return forward;
}

glm::vec3 Camera::GetUp() const
{
	return up;
}

glm::vec3 Camera::GetRight() const
{
	return right;
}

Frustum Camera::GetFrustum() const
{
	return *frustum;
}

float Camera::GetFOV() const
{
	return fov;
}

float Camera::GetNearPlane() const
{
	return nearPlane;
}

float Camera::GetFarPlane() const
{
	return farPlane;
}

void Camera::ProcessMouseMovement(glm::vec2 offset)
{
	offset += 0.01f;
	yaw += offset.x;
	pitch += offset.y;

	if (pitch > 89.0f) {
		pitch = -89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	if (yaw < 0.0f) {
		yaw = 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	UpdateCameraVector();
}

void Camera::ProcessMouseZoom(int y)
{
	if (y < 0 || y > 0) {
		position += static_cast<float>(y) * (forward * 2.0f);
	}
	UpdateCameraVector();
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
	frustum->CalculateFrustum(this);
}
