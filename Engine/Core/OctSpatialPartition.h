#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Rendering/GameObject.h"

constexpr auto CHILDREN_NUMBER = 8;

enum class OctChildren {
	OCT_TLF,
	OCT_BLF,
	OCT_BRF,
	OCT_TRF,
	OCT_TLR,
	OCT_BLR,
	OCT_BRR,
	OCT_TRR
};




class OctNode
{
public:
	OctNode(glm::vec3 position, float size, OctNode* parent);
	~OctNode();
	void Octify(int depth);
	OctNode* GetParent();
	OctNode* GetChild(OctChildren childPos);
	void AddCollisionObject(GameObject* obj);
	int GetObjectCount() const;
	bool IsLeaf() const;
	BoundingBox* GetBoundingBox() const;
	int GetChildCount() const;

	std::vector<GameObject*> objectList;
private:
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];
	float size;
	static int childNum;
};

class OctSpatialPartition
{
public:
	OctSpatialPartition(float worldSize);
	~OctSpatialPartition();
	void AddObject(GameObject* obj);
	GameObject* GetCollision(Ray ray);
private:
	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	void AddObjectToCell(OctNode* cell, GameObject* obj);
	void PrepareCollisionQuery(OctNode* cell, Ray ray);
};
#endif