#include "CollisionHandler.h"
#include "../Core/EngineCore.h"


std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler::CollisionHandler()
{

	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize)
{
	prevCollisions.clear();
	scenePartition = new OctSpatialPartition(worldSize);
}

void CollisionHandler::AddObject(GameObject* go)
{
	if (scenePartition != nullptr) {
		scenePartition->AddObject(go);
	}
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePos, int buttonType)
{
	glm::vec2 tmp(EngineCore::GetInstance()->GetScreenWidth(), EngineCore::GetInstance()->GetScreenHeight());
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePos, tmp, EngineCore::GetInstance()->GetCamera());

	if (scenePartition != nullptr) {
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);
		float shortestDistance = 100000.0f;

		if (hitResult) {
			hitResult->SetHit(true, buttonType);
		}
		for (auto c : prevCollisions) {
			if (hitResult != c && c != nullptr) {
				c->SetHit(false, buttonType);
			}
			c = nullptr;
		}
	
		prevCollisions.clear();
		if (hitResult) {
			prevCollisions.push_back(hitResult);
		}
	}
}

void CollisionHandler::OnDestroy()
{
	delete scenePartition;
	scenePartition = nullptr;

	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();
}
