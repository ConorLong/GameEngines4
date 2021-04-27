#include "BoundingBox.h"

glm::vec3 BoundingBox::OrientMin(glm::vec3& normal)
{
	glm::vec3 min = minVert;

	if (normal.x >= 0) {
		min.x = maxVert.x;
	}
	if (normal.y >= 0) {
		min.y = maxVert.y;
	}
	if (normal.z >= 0) {
		min.z = maxVert.z;
	}
	return(min);
}

glm::vec3 BoundingBox::OrientMax(glm::vec3& normal)
{
	glm::vec3 max = maxVert;

	if (normal.x >= 0) {
		max.x = minVert.x;
	}
	if (normal.y >= 0) {
		max.y = minVert.y;
	}
	if (normal.z >= 0) {
		max.z = minVert.z;
	}
	return(max);
}
