#include "GameScene.h"


GameScene::GameScene() : shape(nullptr), cube(nullptr), model(nullptr)
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
}

bool GameScene::OnCreate()
{
	Debug::Info("Game scene created" , __FILE__, __LINE__);
	
	EngineCore::GetInstance()->SetCamera(new Camera());
	EngineCore::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f, 0.5f));
	EngineCore::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));

#pragma region Textures
	TextureHandler::GetInstance()->CreateTexture("RAMTexture", "./Resources/Images/RAM.jpg");
	TextureHandler::GetInstance()->CreateTexture("RAMTexture", "./Resources/Images/Alive1997.jpg");
	TextureHandler::GetInstance()->CreateTexture("RAMTexture", "./Resources/Images/Alive2007.jpg");
	TextureHandler::GetInstance()->CreateTexture("RAMTexture", "./Resources/Images/Homework.jpg");
	TextureHandler::GetInstance()->CreateTexture("RAMTexture", "./Resources/Images/Human.jpg");
#pragma endregion

	//TextureHandler::GetInstance()->CreateTexture("CheckerBoardTexture", "./Resources/Images/CheckerboardTexture.png");

	model = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"));
	model->AddMesh(cubeMesh = new Mesh(cube->GetFaces(),
			TextureHandler::GetInstance()->GetTexture("RAMTexture"),
			ShaderHandler::GetInstance()->GetShader("basicShader")));

	
	model->SetScale(glm::vec3(0.5f));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime)
{
	model->SetAngle(model->GetAngle() + 0.010f);
}

void GameScene::Render()
{
	shape->Render(EngineCore::GetInstance()->GetCamera());
}
