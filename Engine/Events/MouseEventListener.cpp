#include "MouseEventListener.h"
#include"../Core/EngineCore.h"

EngineCore* MouseEventListener::engineInstance = nullptr;
glm::ivec2 MouseEventListener::mouse = glm::ivec2();
glm::ivec2 MouseEventListener::prevMouse = glm::ivec2();
bool MouseEventListener::firstUpdate = true;
MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(EngineCore* engine)
{
	engineInstance = engine;
}

void MouseEventListener::Update(SDL_Event e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		UpdateMousePosition();
		NotifyOfMousePressed(e.button.button);
	}
	else if (e.type == SDL_MOUSEBUTTONUP) {
		UpdateMousePosition();
		NotifyOfMouseReleased(e.button.button);
	}else if (e.type == SDL_MOUSEMOTION) {
		UpdateMousePosition();
		NotifyOfMouseMove();
	}
	else if (e.type == SDL_MOUSEWHEEL) {
		UpdateMousePosition();
		NotifyOfMouseScroll(e.wheel.y);
	}

}

void MouseEventListener::NotifyOfMousePressed(int buttonType)
{
	if (engineInstance) {
		engineInstance->NotifyOfMousePress(mouse, buttonType);
	}
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType)
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseRelease(mouse, buttonType);
	}
}

void MouseEventListener::NotifyOfMouseMove()
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseMove(mouse);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y)
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseScroll(y);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return prevMouse;
}

glm::vec2 MouseEventListener::GetMousePosition()
{
	return mouse;
}

glm::vec2 MouseEventListener::GetMouseOffset()
{
	return glm::vec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePosition()
{
	int tmpx, tmpy;
	SDL_GetMouseState(&tmpx, &tmpy);

	tmpy = static_cast<int>(engineInstance->GetScreenHeight()) - tmpy;
	if (firstUpdate) {
		prevMouse.x = mouse.x = tmpx;
		prevMouse.y = mouse.y = tmpy;
		firstUpdate = false;
	}
	else {
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tmpx;
		mouse.y = tmpy;
	}
}
