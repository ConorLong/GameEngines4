#include "EventListener.h"
#include "../Core/EngineCore.h"

EventListener::EventListener() 
{

}
EventListener::~EventListener()
{
}

void EventListener::Update()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_QUIT) {
			EngineCore::GetInstance()->Exit();
		}
		switch (sdlEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			MouseEventListener::Update(sdlEvent);
		default:
			break;
		}
	}
}
