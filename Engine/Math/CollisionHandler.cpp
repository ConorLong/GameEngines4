#include "CollisionHandler.h"
#include "../Core/EngineCore.h"


std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();

CollisionHandler::CollisionHandler()
{
	colliders.reserve(10);
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

void CollisionHandler::OnCreate()
{
	colliders.clear();
	prevCollisions.clear();
}

void CollisionHandler::AddObject(GameObject* go)
{
	colliders.push_back(go);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePos, int buttonType)
{
	glm::vec2 tmp(EngineCore::GetInstance()->GetScreenWidth(), EngineCore::GetInstance()->GetScreenHeight());
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePos, tmp, EngineCore::GetInstance()->GetCamera());

	GameObject* hitResult = nullptr;
	float shortestDistance = 100000.0f;

	for (auto g : colliders) {
		if (mouseRay.IsColliding(&g->GetBoundingBox())) {
			if (mouseRay.intersectionDist < shortestDistance) {
				hitResult = g;
				shortestDistance = mouseRay.intersectionDist;
			}
		}
	}

	if (hitResult) {
		hitResult->SetHit(true, buttonType);
	}
	for (auto c : prevCollisions) {
		if (hitResult != c && c != nullptr) {
			c->SetHit(false, buttonType);
		}
	}

	prevCollisions.clear();
	if (hitResult) {
		prevCollisions.push_back(hitResult);
	}
}

void CollisionHandler::OnDestroy()
{
	for (auto entry : colliders) {
		entry = nullptr;
	}
	colliders.clear();

	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();
}
