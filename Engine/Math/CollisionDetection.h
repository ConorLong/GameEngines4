#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Rendering/Camera.h"

struct Ray;
struct BoundingBox;

class CollisionDetection
{
public:

	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator=(const CollisionDetection&) = delete;
	CollisionDetection& operator= (CollisionDetection&&) = delete;

	CollisionDetection() = delete;
	~CollisionDetection();

	static Ray MousePosToWorldRay(glm::vec2 mouseCoords, glm::vec2 screenSize, Camera* cam);
	static bool RayObbIntersection(Ray* ray, BoundingBox* box);
};
#endif
