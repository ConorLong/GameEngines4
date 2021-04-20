#ifndef FRUSTUM_H
#define FRUSTUM_H
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew.h>
#include "../Math/BoundingBox.h"
#include "Camera.h"
class Frustum
{
private:
	enum plane {
		A = 0,
		B = 1,
		C = 2,
		D = 3
	};
	enum sides {
		RIGHT = 0,
		LEFT = 1,
		TOP = 2,
		BOTTOM = 3,
		NEAR = 4,
		FAR = 5
	};

	float frustum[6][4];
public:

	Frustum();
	~Frustum();
	void CalculateFrustum();
	void NormalizePlane(float frus[6][4], int side);
	bool CheckBox(BoundingBox &box);
};
#endif
