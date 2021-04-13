#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

#include <../../SDL/include/SDL.h>
#include<../include/glm/glm.hpp>

class EngineCore;

class MouseEventListener
{
public:
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator= (MouseEventListener&&) = delete;

	MouseEventListener() = delete;
	~MouseEventListener();

	static void RegisterEngineObject(EngineCore* engine);
	static void Update(SDL_Event e);

	static void NotifyOfMousePressed(int buttonType);
	static void NotifyOfMouseReleased(int buttonType);
	static void NotifyOfMouseMove();
	static void NotifyOfMouseScroll(int y);

	static glm::vec2 GetPreviousMousePosition();
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetMouseOffset();
private:
	static EngineCore* engineInstance;
	static glm::ivec2 mouse, prevMouse;
	static bool firstUpdate;

	static void UpdateMousePosition();

	
};
#endif
