#include "GameScene.h"


GameScene::GameScene() : shape(nullptr), cube(nullptr), model(nullptr), light1(nullptr), light2(nullptr), cubeMesh(nullptr)
{
	cube = new Cube(5.0f);
}

GameScene::~GameScene()
{
	
	cubeMesh = nullptr;
	delete cubeMesh;
	model = nullptr;
	delete shape;
	shape = nullptr;
	
	delete cube;
	cube = nullptr;

	EngineCore::GetInstance()->GetCamera()->OnDestroy();
}

bool GameScene::OnCreate()
{
	Debug::Info("Game scene created" , __FILE__, __LINE__);

	light1 = new LightSource(glm::vec3(-3.0f, 2.0f, 2.0f), glm::vec3(0.8f, 0.2f, 0.8f), 0.1f, 0.5f, 0.5f);
	light2 = new LightSource(glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(0.5f, 0.3f, 0.8f), 0.1f, 0.5f, 0.5f);

	EngineCore::GetInstance()->SetCamera(new Camera());

	EngineCore::GetInstance()->GetCamera()->AddLightSource(light1);
	EngineCore::GetInstance()->GetCamera()->AddLightSource(light2);

	EngineCore::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));

#pragma region Textures
	TextureHandler::GetInstance()->CreateTexture("RAMTexture", "./Resources/Images/RAM.jpg");
	TextureHandler::GetInstance()->CreateTexture("Alive1997Texture", "./Resources/Images/Alive1997.jpg");
	TextureHandler::GetInstance()->CreateTexture("Alive2007Texture", "./Resources/Images/Alive2007.jpg");
	TextureHandler::GetInstance()->CreateTexture("HomeworkTexture", "./Resources/Images/Homework.jpg");
	TextureHandler::GetInstance()->CreateTexture("HumanTexture", "./Resources/Images/Human.jpg");
#pragma endregion

	model = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"), "Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl");
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime)
{
	shape->Update(deltaTime);
}

void GameScene::Render()
{
	shape->Render(EngineCore::GetInstance()->GetCamera());
}
