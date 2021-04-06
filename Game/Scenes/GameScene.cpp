#include "GameScene.h"


GameScene::GameScene() : light1(nullptr), light2(nullptr)
{
}

GameScene::~GameScene()
{
	EngineCore::GetInstance()->GetCamera()->OnDestroy();
}

bool GameScene::OnCreate()
{
	Debug::Info("Game scene created" , __FILE__, __LINE__);

	light1 = new LightSource(glm::vec3(-8.0f, 2.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, 0.3f, 0.8f);
	//light2 = new LightSource(glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f, 0.5f);

	EngineCore::GetInstance()->SetCamera(new Camera());

	EngineCore::GetInstance()->GetCamera()->AddLightSource(light1);
	//EngineCore::GetInstance()->GetCamera()->AddLightSource(light2);

	EngineCore::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));

#pragma region Textures
	TextureHandler::GetInstance()->CreateTexture("RAMTexture", "./Resources/Images/RAM.jpg");
	TextureHandler::GetInstance()->CreateTexture("Alive1997Texture", "./Resources/Images/Alive1997.jpg");
	TextureHandler::GetInstance()->CreateTexture("Alive2007Texture", "./Resources/Images/Alive2007.jpg");
	TextureHandler::GetInstance()->CreateTexture("HomeworkTexture", "./Resources/Images/Homework.jpg");
	TextureHandler::GetInstance()->CreateTexture("HumanTexture", "./Resources/Images/Human.jpg");

#pragma endregion

	Model* diceModel = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"), "Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl");
	Model* appleModel = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"), "Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl");

	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(appleModel);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(-2.0f, 0.0f, -2.0f)));
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(3.0f, 0.0f, 0.0f)), "Apple");

	diceModel = nullptr;
	appleModel = nullptr;
	return true;
}

void GameScene::Update(const float deltaTime)
{
	SceneGraph::GetInstance()->Update(deltaTime);
}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(EngineCore::GetInstance()->GetCamera());
}
