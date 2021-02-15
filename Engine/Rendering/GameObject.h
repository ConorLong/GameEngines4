#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
class GameObject
{
public:
	GameObject(Model* m);
	~GameObject();

	void Render();

private:
	Model* model;
};
#endif
