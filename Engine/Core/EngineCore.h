#ifndef ENGINECORE_H
#define ENGINECORE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "../../Game/Scenes/Scene.h"

#include "../Rendering/GameObject.h"

#include "../Graphics/ShaderHandler.h"

#include "../Rendering/Camera.h"
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

	float GetScreenWidth() const;
	float GetScreenHeight() const;

	bool GetIsRunning() const;
	int GetCurrentScene() const;
	Camera* GetCamera() const;
	static EngineCore* GetInstance();

	void SetCurrentScene(int sceneNum);
	void SetGameInterface(GameInterface* interface);
	void SetCamera(Camera* camera);
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
	Camera* camera;
	static std::unique_ptr<EngineCore> s_engine;
	friend std::default_delete<EngineCore>;
};
#endif

