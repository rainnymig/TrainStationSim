#pragma once

#include <unordered_map>
#include <string_view>
#include <functional>
#include <list>

namespace tss
{
	class Event
	{
	public:
		virtual std::string_view getType() const = 0;
	};

	class EventBus
	{
	public:
		void AddEventListener(const Event& aEvent, std::function<void(const Event&)> aEventHandler);
		void RaiseEvent(const Event& aEvent);
		
	private:
		std::unordered_map<std::string_view, std::list<std::function<void(const Event&)>>> eventHandlers;
	};
}