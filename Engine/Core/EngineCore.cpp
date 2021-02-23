#include "EngineCore.h"


 std::unique_ptr<EngineCore> EngineCore::s_engine = nullptr;

EngineCore::EngineCore() : window(nullptr), isRunning(false), fps(60), gInterface(nullptr), currentScene(0)
{

}

EngineCore::~EngineCore()
{
	OnDestroy();
}

 EngineCore* EngineCore::GetInstance()
{
	if (s_engine.get() == nullptr) {
		s_engine.reset(new EngineCore);
	}
	return s_engine.get();
}

 void EngineCore::SetCurrentScene(int sceneNum)
 {
	 currentScene = sceneNum;
 }

bool EngineCore::OnCreate(std::string name, int width, int height)
{
	Debug::OnCreate();
	window = new Window();
	if (!window->OnCreate(name, width, height)) {
		Debug::FatalError("Window failed to init", __FILE__, __LINE__);
		OnDestroy();
		
		return isRunning = false;
	}

	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");

	if (gInterface != nullptr) {
		if (!gInterface->OnCreate()) {
			Debug::FatalError("Game failed to init", __FILE__, __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}
	Debug::Info("Everything worked", __FILE__, __LINE__);
	timer.Start();
	return isRunning = true;
}

void EngineCore::Run()
{
	while (isRunning) {
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	if (!isRunning) {
		OnDestroy();
	}
}

void EngineCore::Exit()
{
	isRunning = false;
}


void EngineCore::SetGameInterface(GameInterface* interface) 
{
	gInterface = interface;
}

bool EngineCore::GetIsRunning() const
{
	return isRunning;
}

int EngineCore::GetCurrentScene() const
{
	return currentScene;
}

void EngineCore::Update(const float deltaTime)
{
	if (gInterface != nullptr) {
		gInterface->Update(deltaTime);
		std::cout << deltaTime << std::endl;
	}
}

void EngineCore::Render()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gInterface != nullptr) {
		gInterface->Render();
	}
	//Render
	SDL_GL_SwapWindow(window->GetWindow());
}

void EngineCore::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();
	delete gInterface;
	gInterface = nullptr;
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}

