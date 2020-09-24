#pragma once

#include "../event/Event.h"

class KeyPressEvent : public Event
{
	const int key;
	const int scancode;
	const int action;
	const int mods;


public:
	KeyPressEvent(int key, int scancode, int action, int mods);
};

