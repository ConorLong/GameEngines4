#ifndef GAME1_H
#define GAME1_H

#include"../Engine/Core/EngineCore.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"


class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1();

	bool OnCreate() override;
	void Update(const float deltaTime) override;
	void Render() override;

private:
	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();

};
#endif