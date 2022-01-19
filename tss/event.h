#pragma once

#include "id.h"

#include <functional>
#include <unordered_map>

namespace tss
{
	template<typename E>
	class EventEmitter
	{
	public:
		IdType addEventHandler(std::function<bool(const E&)> aEventHandler);
		void removeEventHandler(const IdType aEventHandlerId);
		void emit(const E& aEvent);
		
	private:
		std::unordered_map<IdType, std::function<bool(const E&)>> eventHandlers;
		IdType id = 1;

		IdType generateId();
	};

	template<typename E>
	inline IdType EventEmitter<E>::addEventHandler(std::function<bool(const E&)> aEventHandler)
	{
		const IdType newId = generateId();
		eventHandlers[newId] = aEventHandler;
		return newId;
	}

	template<typename E>
	inline void EventEmitter<E>::removeEventHandler(const IdType aEventHandlerId)
	{
		eventHandlers.erase(aEventHandlerId);
	}

	template<typename E>
	inline void EventEmitter<E>::emit(const E& aEvent)
	{
		for (const auto& handler : eventHandlers)
		{
			handler(aEvent);
		}
	}

	template<typename E>
	inline IdType EventEmitter<E>::generateId()
	{
		return id++;
	}
}