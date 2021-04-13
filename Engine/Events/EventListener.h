#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "EventListener.h"
#include "MouseEventListener.h"

class EventListener
{
	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	EventListener& operator=(const EventListener&) = delete;
	EventListener& operator= (EventListener&&) = delete;

	EventListener();
	~EventListener();
public:
	static void Update();
};
#endif
