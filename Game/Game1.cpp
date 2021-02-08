
#include "Game1.h"


Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr)
{
}

Game1::~Game1()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	if (EngineCore::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::Error("Scene did not create", __FILE__, __LINE__);
	return false;
}

void Game1::Update(const float deltaTime)
{
	if (currentSceneNum != EngineCore::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime);
	
}

void Game1::Render()
{
	currentScene->Render();
}

void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (EngineCore::GetInstance()->GetCurrentScene()) {
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = EngineCore::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		Debug::Error("Scene did not create", __FILE__, __LINE__);
		EngineCore::GetInstance()->Exit();
	}
}
