#ifndef BOUNDINGBOX_H	
#define BOUNDINGBOX_H

#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>

struct BoundingBox
{
	
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;
	glm::vec3 points[4];

	inline BoundingBox() 
	{
		maxVert = minVert = glm::vec3();
		transform = glm::mat4();
	}

	inline BoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_) 
	{
		maxVert = maxVert_;
		minVert = minVert_;
		transform = transform_;
	}

	glm::vec3 OrientMin(glm::vec3& normal);
	glm::vec3 OrientMax(glm::vec3& normal);

	inline bool Intersects(BoundingBox* box) {
		glm::vec3 minCorner = GetTransformedPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, transform);

		glm::vec3 otherMinCorner = GetTransformedPoint(box->minVert, box->transform);
		glm::vec3 otherMaxCorner = GetTransformedPoint(box->minVert, box->transform);
		return true;
	}

private:
	inline glm::vec3 GetTransformedPoint(glm::vec3 point, glm::mat4 transform_) {
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point;
	}
};
#endif
