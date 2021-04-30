
#include "Frustum.h"

Frustum::Frustum()
{
	
}
Frustum::~Frustum()
{
}
void Frustum::CalculateFrustum(Camera* camera)
{

	float hNear = 2 * tan(camera->GetFOV() / 2) * camera->GetNearPlane();
	float wNear = hNear * (EngineCore::GetInstance()->GetScreenWidth() / EngineCore::GetInstance()->GetScreenHeight());

	float hFar = 2 * tan(camera->GetFOV() / 2) * camera->GetFarPlane();
	float wFar = hFar * (EngineCore::GetInstance()->GetScreenWidth() / EngineCore::GetInstance()->GetScreenHeight());

	glm::vec3 camPos = camera->GetPosition();

	// These are normalized in camera 
	glm::vec3 forward = camera->GetForward();
	glm::vec3 up = camera->GetUp();
	glm::vec3 right = camera->GetRight();

	//Determine center of far plane, with that we can calculate the corners of our far plane by dividing our already known height and width by 2
	glm::vec3 fCenterPoint = camPos + forward * camera->GetFarPlane();

	glm::vec3 farTL = fCenterPoint + (up * (hFar / 2)) - (right * (wFar / 2));
	glm::vec3 farTR = fCenterPoint + (up * (hFar / 2)) + (right * (wFar / 2));
	glm::vec3 farBL = fCenterPoint - (up * (hFar / 2)) - (right * (wFar / 2));
	glm::vec3 farBR = fCenterPoint - (up * (hFar / 2)) + (right * (wFar / 2));

	glm::vec3 nCenterPoint = camPos + forward * camera->GetNearPlane();

	glm::vec3 nearTL = nCenterPoint + (up * (hNear / 2)) - (right * (wNear / 2));
	glm::vec3 nearTR = nCenterPoint + (up * (hNear / 2)) + (right * (wNear / 2));
	glm::vec3 nearBL = nCenterPoint - (up * (hNear / 2)) - (right * (wNear / 2));
	glm::vec3 nearBR = nCenterPoint - (up * (hNear / 2)) + (right * (wNear / 2));

	//Now we have 8 points and 6 planes
	p[0] = p[0].CreatePlaneFrom3Points(nearTR, nearTL, farTL);
	p[1] = p[1].CreatePlaneFrom3Points(nearBL, nearBR, farBR);
	p[2] = p[2].CreatePlaneFrom3Points(nearTL, nearBL, farBL);
	p[3] = p[3].CreatePlaneFrom3Points(nearBR, nearTR, farBR);
	p[4] = p[4].CreatePlaneFrom3Points(nearTL, nearTR, nearBR);
	p[5] = p[5].CreatePlaneFrom3Points(farTR, farTL, farBL);
}

void Frustum::NormalizePlane(float frus[6][4], int side)
{

}

bool Frustum::CheckBox(BoundingBox &box)
{
	for (int i = 0; i < 6; i++) {
		glm::vec3 min = box.OrientMin(p[i].normal);
		glm::vec3 max = box.OrientMax(p[i].normal);

		float tmp = p[i].SignedDistance(min);
		if (tmp < 0) {
			return false;
		}
		else if (p[i].SignedDistance(max) < 0) {
			//intersect
			return true;
		}

	}
	return true;
}

bool Frustum::CheckPoints(BoundingBox& box)
{
	for (int i = 0; i < 6; i++) {
		if (p[i].SignedDistance(box.maxVert) < 0) {
			return false;
		}
		else if (p[i].SignedDistance(box.minVert) < 0) {
			return false;
		}
	}
	return true;
}
