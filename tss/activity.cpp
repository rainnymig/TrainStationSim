#include "activity.h"

namespace tss
{
	Activity::Activity()
		: Activity(nullptr, nullptr, NULL_ID)
	{
	}

	Activity::Activity(ActivityData* aData, ActivityProcess* aProcess, const IdType aConnectedSpace)
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

	bool Activity::addPeople(IdType aPassenger, std::function<bool(const ActivityEvent&)> aActivityUpdateHandler)
	{
		if (passengerHandlerMap.contains(aPassenger))
		{
			return true;
		}

		const IdType handlerId = eventEmitter.addEventHandler(aActivityUpdateHandler);

		passengerHandlerMap[aPassenger] = handlerId;

		return false;
	}

	void Activity::removePeople(IdType aPassenger)
	{
		if (!passengerHandlerMap.contains(aPassenger))
		{
			return;
		}

		eventEmitter.removeEventHandler(passengerHandlerMap.at(aPassenger));
		passengerHandlerMap.erase(aPassenger);
	}
}