#include "EventBus.h"

#include "../events/KeyPressEvent.h"
#include "Event.h"
#include <iostream>


void EventBus::Fire(Event& event)
{
	std::cout << "Event fired: " << typeid(event).name() << std::endl;
	auto& e = reinterpret_cast<KeyPressEvent&>(event);
	std::cout << "Event fired: " << typeid(e).name() << std::endl;
}

template<class T>
void EventBus::Register()
{
	
}
