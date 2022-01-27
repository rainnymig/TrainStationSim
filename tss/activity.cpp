#include "activity.h"

namespace tss
{
	Activity::Activity()
		: Activity(nullptr, nullptr, NULL_ID)
	{
	}

	Activity::Activity(const ActivityData* aData, const ActivityProcess* aProcess, const IdType aConnectedSpace)
		: data(aData)
		, process(aProcess)
		, connectedSpace(aConnectedSpace)
		, id(generateId())
	{
	}

	std::string_view Activity::getType() const
	{
		return data->type;
	}

	void Activity::update(const Station& aStation)
	{
		processPeopleInTheFront(process->peoplePerMinute);
	}

	size_t Activity::getPeopleCount() const
	{
		return passengerHandlerMap.size();
	}

	void Activity::setConnectedSpace(const IdType aConnectedSpace)
	{
		connectedSpace = aConnectedSpace;
	}

	IdType Activity::getConnectedSpace() const
	{
		return connectedSpace;
	}

	bool Activity::canEnter(const Passenger& aPassenger, const Station& aStation) const
	{
		return passengerQueue.size() < process->maxQueueLength && data->canEnter(aPassenger, aStation);
	}

	void Activity::addPeople(IdType aPassenger, std::function<bool(const ActivityEvent&)> aActivityUpdateHandler)
	{
		if (passengerHandlerMap.contains(aPassenger))
		{
			return;
		}

		const IdType handlerId = eventEmitter.addEventHandler(aActivityUpdateHandler);
		passengerHandlerMap[aPassenger] = handlerId;
		passengerQueue.emplace_back(aPassenger);
	}

	void Activity::removePeople(IdType aPassenger)
	{
		if (!passengerHandlerMap.contains(aPassenger))
		{
			return;
		}

		eventEmitter.removeEventHandler(passengerHandlerMap.at(aPassenger));
		passengerHandlerMap.erase(aPassenger);
		std::erase(passengerQueue, aPassenger);
	}

	void Activity::processPeopleInTheFront(size_t aCount)
	{
		if (passengerQueue.empty())
		{
			return;
		}
		size_t peopleCountToRemove = std::min(passengerQueue.size(), aCount);
		while (peopleCountToRemove-- > 0)
		{
			IdType people = passengerQueue.front();
			eventEmitter.removeEventHandler(passengerHandlerMap.at(people));
			passengerHandlerMap.erase(people);
			passengerQueue.pop_front();
		}
	}
}