#ifndef ENGINECORE_H
#define ENGINECORE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "../../Game/Scenes/Scene.h"

#include "../Rendering/GameObject.h"
class EngineCore
{
public:
	EngineCore(const EngineCore&) = delete;
	EngineCore(EngineCore&&) = delete;
	EngineCore& operator=(const EngineCore&) = delete;
	EngineCore& operator= (EngineCore&&) = delete;

	bool OnCreate(std::string name, int width, int height);
	void Run();
	void Exit();

	bool GetIsRunning() const;
	int GetCurrentScene() const;
	static EngineCore* GetInstance();

	void SetCurrentScene(int sceneNum);
	void SetGameInterface(GameInterface* interface);
private:


	EngineCore();
	~EngineCore();
	void Update(const float deltaTime);
	void Render();
	void OnDestroy();

	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;
	int currentScene;

	GameInterface* gInterface;

	static std::unique_ptr<EngineCore> s_engine;
	friend std::default_delete<EngineCore>;
};
#endif

