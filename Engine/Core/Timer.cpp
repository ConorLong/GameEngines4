#include "Timer.h"

Timer::Timer() : prevTicks(0), currentTicks(0)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	prevTicks = currentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks()
{
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
	unsigned int mSecsPerFrame = MILLI_TO_SEC / fps_;
	if (mSecsPerFrame == 0) {
		return 0;
	}
	unsigned int sleepTime = mSecsPerFrame - (SDL_GetTicks() - currentTicks);
	if (sleepTime > mSecsPerFrame) {
		return mSecsPerFrame;
	}
	return sleepTime;
}

float Timer::GetDeltaTime() const
{
	return (currentTicks - prevTicks) / MILLI_TO_SEC;
}

float Timer::GetCurrentTickMilli() const
{
	return static_cast<float>(currentTicks);
}

float Timer::GetCurrentTickSec() const
{
	return currentTicks / MILLI_TO_SEC;
}
