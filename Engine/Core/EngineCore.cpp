#include "EngineCore.h"

 std::unique_ptr<EngineCore> EngineCore::s_engine = nullptr;

EngineCore::EngineCore() : window(nullptr), isRunning(false)
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

bool EngineCore::OnCreate(std::string name, int width, int height)
{
	window = new Window();
	if (!window->OnCreate(name, width, height)) {
		std::cout << "Window failed to init" << std::endl;
		OnDestroy();
		
		return isRunning = false;
	}
	return isRunning = true;
}

void EngineCore::Run()
{
	while (isRunning) {
		Update(0.016f);
		Render();
	}
	if (!isRunning) {
		OnDestroy();
	}
}

bool EngineCore::GetIsRunning()
{
	return isRunning;
}

void EngineCore::Update(const float deltaTime)
{
}

void EngineCore::Render()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Render
	SDL_GL_SwapWindow(window->GetWindow());
}

void EngineCore::OnDestroy()
{
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}
