#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/EngineCore.h"

class GameScene: public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	bool OnCreate() override;
	void Update(const float deltaTime) override;
	void Render() override;

private:
	LightSource* light2;
	LightSource* light1;
};
#endif
