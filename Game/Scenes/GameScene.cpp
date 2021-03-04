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
	EngineCore::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));

	//TextureHandler::GetInstance()->CreateTexture("CheckerBoardTexture", "./Resources/Images/CheckerboardTexture.png");
	TextureHandler::GetInstance()->CreateTexture("RAMTexture", "./Resources/Images/RAM.jpg");

	model = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"));
	model->AddMesh(cubeMesh = new Mesh(cube->GetFaces(),
			TextureHandler::GetInstance()->GetTexture("RAMTexture"),
			ShaderHandler::GetInstance()->GetShader("basicShader")));

	//cubeMesh->SetRenderOption(RenderOptions::CUBETEXTURE);
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
