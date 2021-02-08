#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	Debug::Info("Start scene created", __FILE__, __LINE__);
	return true;
}

void StartScene::Update(const float deltaTime)
{
	if (EngineCore::GetInstance()->GetCurrentScene() == 0) {
		EngineCore::GetInstance()->SetCurrentScene(1);
	}
}

void StartScene::Render()
{
}