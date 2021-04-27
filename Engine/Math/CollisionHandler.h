#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Ray.h"
#include "../Rendering/GameObject.h"
#include "CollisionDetection.h"
#include "../Core/OctSpatialPartition.h"

class CollisionHandler
{
public:

	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator= (CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();

	void OnCreate(float worldSize);
	void AddObject(GameObject* go);
	void MouseUpdate(glm::vec2 mousePos, int buttonType);
	void OnDestroy();

private:
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionInstance;
	friend std::default_delete<CollisionHandler>;

	static OctSpatialPartition* scenePartition;
	static std::vector<GameObject*> prevCollisions;

};
#endif
