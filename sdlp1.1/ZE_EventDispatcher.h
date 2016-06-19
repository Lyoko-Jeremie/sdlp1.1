#pragma once
#include <functional>
#include <SDL.h>
#include "ZE_EventContainer.h"

using namespace std;

//���п�ע���¼���Ļ���
class EventDispatcher
{
public:
	EventDispatcher();
	EventDispatcher(size_t dispatch_index);
	virtual ~EventDispatcher();
	void addEventListener(EventMode event_mode, Uint32 type, function<void(SDL_Event)>);
	void removeEventListeners(SDL_EventType type) const;
	void removeEventListeners(EventMode type) const;
	void removeAllEvents() const;
public:
	const size_t dispatch_index;
};

