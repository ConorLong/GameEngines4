#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "Scene.h"
#include "../../Engine/Core/EngineCore.h"

class StartScene: public Scene
{
public:
	StartScene();
	virtual ~StartScene();

	bool OnCreate() override;
	void Update(const float deltaTime) override;
	void Render() override;
};
#endif
