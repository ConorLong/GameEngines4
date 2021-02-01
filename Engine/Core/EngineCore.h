#ifndef ENGINECORE_H
#define ENGINECORE_H

#include <memory>
#include "Window.h"
class EngineCore
{
public:
	EngineCore(const EngineCore&) = delete;
	EngineCore(EngineCore&&) = delete;
	EngineCore& operator=(const EngineCore&) = delete;
	EngineCore& operator= (EngineCore&&) = delete;

	bool OnCreate(std::string name, int width, int height);
	void Run();
	bool GetIsRunning();

	static EngineCore* GetInstance();
private:


	EngineCore();
	~EngineCore();
	void Update(const float deltaTime);
	void Render();
	void OnDestroy();

	Window* window;
	bool isRunning;
	static std::unique_ptr<EngineCore> s_engine;
	friend std::default_delete<EngineCore>;
};
#endif

