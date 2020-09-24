#pragma once
#include <functional>
#include <vector>
template<typename T> class Event;

template<typename Return, typename... Args>
class Event<Return(Args...)>
{
	std::vector<std::function<Return(Args...)>> events;

public:
	void Register(std::function<Return(Args...)>);
	void Invoke(Args... args);
};


template <typename Return, typename ... Args>
void Event<Return(Args ...)>::Register(std::function<Return(Args...)> method)
{
	events.push_back(method);
}


template <typename Return, typename ... Args>
void Event<Return(Args ...)>::Invoke(Args ... args)
{
	for (auto& event : events)
		event(args...);
}

