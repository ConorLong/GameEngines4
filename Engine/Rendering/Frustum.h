#ifndef FRUSTUM_H
#define FRUSTUM_H
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew.h>

#include "../Math/BoundingBox.h"
#include "../Core/EngineCore.h"
#include "../Math/Plane.h"
class Frustum
{
private:
	
	Plane p[6];
public:

	Frustum();
	~Frustum();
	void CalculateFrustum(Camera* camera);
	void NormalizePlane(float frus[6][4], int side);
	bool CheckBox(BoundingBox &box);
	bool CheckPoints(BoundingBox& box);
};
#endif
