#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "Event.h"

class EventBus
{
	std::vector<Event> events;
	//std::unordered_map<type_info, std::vector<Event>> events2;

public:
	void Fire(Event& event);
	
	template <class T>
	void Register();
};

