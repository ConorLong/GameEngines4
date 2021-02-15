#include "GameObject.h"

GameObject::GameObject(Model* m) : model(nullptr)
{
	model = m;

}

GameObject::~GameObject()
{
	if (model) {
		delete model;
	}
	model = nullptr;
}

void GameObject::Render()
{
	if (model) {
		model->Render();
	}
}
