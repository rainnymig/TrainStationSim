#include "event.h"

namespace tss
{
	void EventBus::AddEventListener(const Event& aEvent, std::function<void(const Event&)> aEventHandler)
	{
		eventHandlers[aEvent.getType()].emplace_back(aEventHandler);
	}

	void EventBus::RaiseEvent(const Event& aEvent)
	{
		if (eventHandlers.contains(aEvent.getType()))
		{
			for (auto& handler : eventHandlers[aEvent.getType()])
			{
				handler(aEvent);
			}
		}
	}
}