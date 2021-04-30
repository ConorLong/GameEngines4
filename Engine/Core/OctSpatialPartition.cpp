#include "OctSpatialPartition.h"

int OctNode::childNum = 0;

OctNode::OctNode(glm::vec3 position, float size_, OctNode* parent_) : octBounds(nullptr), parent(nullptr), children(), objectList(std::vector<GameObject*>()) {
	objectList.reserve(10);

	octBounds = new BoundingBox();
	octBounds->minVert = position;
	octBounds->maxVert = position + glm::vec3(size);

	size = size_;

	parent = parent_;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		children[i] = nullptr;
	}
}

OctNode::~OctNode()
{
	delete octBounds;
	octBounds = nullptr;

	if (objectList.size() > 0) {
		for (auto obj : objectList) {
			obj = nullptr;
		}
		objectList.clear();
	}
	
	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		if (children[i] != nullptr) {
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth)
{
	if (depth > 0 && this) {
		float half = size / 2.0f;
		children[static_cast<int>(OctChildren::OCT_TLF)] = new OctNode(
			glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_BLF)] = new OctNode(
			glm::vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_BRF)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_TRF)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_TLR)] = new OctNode(
			glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z), half, this);

		children[static_cast<int>(OctChildren::OCT_BLR)] = new OctNode(
			glm::vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z), half, this);

		children[static_cast<int>(OctChildren::OCT_BRR)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z), half, this);

		children[static_cast<int>(OctChildren::OCT_TRR)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z), half, this);

		childNum += 8;
	}

	if (depth > 0 && this) {
		for (int i = 0; i < CHILDREN_NUMBER; i++) {
			children[i]->Octify(depth - 1);
		}
	}
}

OctNode* OctNode::GetParent()
{
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPos)
{
	return children[static_cast<int>(childPos)];
}

void OctNode::AddCollisionObject(GameObject* obj)
{
	objectList.push_back(obj);
}

int OctNode::GetObjectCount() const
{
	return objectList.size();
}

bool OctNode::IsLeaf() const
{
	if (children[0] == nullptr) {
		return true;
	}
	return false;
}

BoundingBox* OctNode::GetBoundingBox() const
{
	return octBounds;
}

int OctNode::GetChildCount() const
{
	return childNum;
}

OctSpatialPartition::OctSpatialPartition(float worldSize) : root(nullptr), rayIntersectionList(std::vector<OctNode*>())
{
	root = new OctNode(glm::vec3((-worldSize / 2.0f)), worldSize, nullptr);
	root->Octify(3);
	std::cout << "There are" << root->GetChildCount() << " child nodes" << std::endl;

	rayIntersectionList.reserve(20);
}

OctSpatialPartition::~OctSpatialPartition()
{
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}

	delete root;
	root = nullptr;
}

void OctSpatialPartition::AddObject(GameObject* obj)
{
	AddObjectToCell(root, obj);
}

GameObject* OctSpatialPartition::GetCollision(Ray ray)
{
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}
	PrepareCollisionQuery(root, ray);
	GameObject* result = nullptr;
	float shortestDistance = FLT_MAX;
	for (auto cell : rayIntersectionList) {
		for (auto obj : cell->objectList) {
			if (ray.IsColliding(&obj->GetBoundingBox())) {
				if (ray.intersectionDist < shortestDistance) {
					result = obj;
					shortestDistance = ray.intersectionDist;
				}
			}
		}
		if (result != nullptr) {
		return result;
		}	
	}
	return nullptr;
}

void OctSpatialPartition::AddObjectToCell(OctNode* cell, GameObject* obj)
{
	if (cell->IsLeaf()) {
		if (obj->GetBoundingBox().Intersects(cell->GetBoundingBox())) {
			cell->AddCollisionObject(obj);
			std::cout << obj->GetID() << " added to " << cell->GetBoundingBox()->minVert.x << ", " << cell->GetBoundingBox()->minVert.x << ", " << cell->GetBoundingBox()->minVert.z << std::endl;
		}
	}
	if(!cell->IsLeaf()){
		for (int i = 0; i < CHILDREN_NUMBER; i++) {
			
			AddObjectToCell(cell->GetChild(static_cast<OctChildren>(i)), obj);
		}
	}
}

void OctSpatialPartition::PrepareCollisionQuery(OctNode* cell, Ray ray)
{
	if (cell->IsLeaf()) {
		if(ray.IsColliding(cell->GetBoundingBox())) {
			rayIntersectionList.push_back(cell);
		}
	}
	else {
		for (int i = 0; i < CHILDREN_NUMBER; i++) {

			PrepareCollisionQuery(cell->GetChild(static_cast<OctChildren>(i)), ray);
		}
	}
}
