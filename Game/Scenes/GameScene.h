#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
class GameScene: public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	bool OnCreate() override;
	void Update(const float deltaTime) override;
	void Render() override;
};
#endif
