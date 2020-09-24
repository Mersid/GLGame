#pragma once
#include <functional>
#include <vector>

template<typename T>
class EventBusTwo
{
	std::vector<std::function<T>> events;
	
public:
	std::function<T> bindhere;
	
	void Register(T method);
	std::vector<std::function<T>>& Events();
	//void Invoke();
};

template <typename T>
void EventBusTwo<T>::Register(T method)
{
	events.push_back(method);
}

template <typename T>
std::vector<std::function<T>>& EventBusTwo<T>::Events()
{
	return events;
}