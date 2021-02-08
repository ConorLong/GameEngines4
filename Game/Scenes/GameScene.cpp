#include "GameScene.h"
#include "../../Engine/Core/Debug.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	
}

bool GameScene::OnCreate()
{
	Debug::Info("Game scene created" , __FILE__, __LINE__);
	return true;
}

void GameScene::Update(const float deltaTime)
{
}

void GameScene::Render()
{
}
