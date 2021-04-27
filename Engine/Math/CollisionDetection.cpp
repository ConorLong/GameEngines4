#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/EngineCore.h"
CollisionDetection::~CollisionDetection()
{
}

Ray CollisionDetection::MousePosToWorldRay(glm::vec2 mouseCoords, glm::vec2 screenSize, Camera* cam)
{
	glm::vec4 rayStartNDC((mouseCoords.x / screenSize.x - 0.5f) * 2.0f, (mouseCoords.y / screenSize.y - 0.5f) * 2.0f , -1.0f, 1.0f);

	glm::vec4 rayEndNDC((mouseCoords.x / screenSize.x - 0.5f) * 2.0f, (mouseCoords.y / screenSize.y - 0.5f) * 2.0f, 0.0f, 1.0f);

	glm::mat4 inverse = glm::inverse(cam->GetPerspective() * cam->GetView());

	glm::vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	glm::vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);

	return Ray(glm::vec3(rayStartWorld), rayDirWorld);
}

bool CollisionDetection::RayObbIntersection(Ray* ray, BoundingBox* box)
{
	glm::mat4 modelMatrix = box->transform;
	glm::vec3 rayOrigin = ray->origin;
	glm::vec3 rayDirection = ray->direction;
	glm::vec3 boxMin = box->minVert;
	glm::vec3 boxMax = box->maxVert;

	float tMin = EngineCore::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = EngineCore::GetInstance()->GetCamera()->GetFarPlane();

	glm::vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	glm::vec3 delta = worldPos - rayOrigin;

	glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = glm::dot(xAxis, delta);
	float dotDir = glm::dot(rayDirection, xAxis);

	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.x) / dotDir;
		float t2 = (dotDelta + boxMax.x) / dotDir;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f) {
			return false;
		}
	}

	glm::vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
	dotDelta = glm::dot(yAxis, delta);
	dotDir = glm::dot(rayDirection, yAxis);

	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.y) / dotDir;
		float t2 = (dotDelta + boxMax.y) / dotDir;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDelta + boxMin.y > 0.0f || -dotDelta + boxMax.y < 0.0f) {
			return false;
		}
	}

	glm::vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
	dotDelta = glm::dot(zAxis, delta);
	dotDir = glm::dot(rayDirection, zAxis);

	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.z) / dotDir;
		float t2 = (dotDelta + boxMax.z) / dotDir;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDelta + boxMin.z > 0.0f || -dotDelta + boxMax.z < 0.0f) {
			return false;
		}
	}
	ray->intersectionDist = tMin;
	return true;
}
