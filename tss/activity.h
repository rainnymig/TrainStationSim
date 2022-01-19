#pragma once

#include "clock.h"
#include "id.h"

#include "event.h"

#include <memory>
#include <string_view>
#include <functional>
#include <unordered_map>
#include <set>

namespace tss
{
	class Passenger;
	class Station;

	struct ActivityData
	{
		std::string_view type;

		float mood;
		float frustration;
		float hunger;
		float thirst;
		float toiletWill;
		float health;
		float entertainment;
		
		std::function<bool(const Passenger&, const Station&)> canEnter;
	};

	struct ActivityProcess
	{
		size_t peoplePerMinute;
		size_t maxQueueLength;
	};

	struct ActivityEvent
	{
		IdType passenger;
	};

	class Activity
	{
	public:
		IdType id;
		ActivityData* data;
		ActivityProcess* process;

		Activity();
		Activity(ActivityData* aData, ActivityProcess* aProcess, const IdType aConnectedSpace = NULL_ID);
		Activity(const Activity&) = default;
		Activity(Activity&&) = default;
		Activity& operator=(const Activity&) = default;
		Activity& operator=(Activity&&) = default;

		std::string_view getType() const;

		void update(const Station& aStation);
		size_t getPeopleCount() const;

		void setConnectedSpace(const IdType aNextSpace);
		IdType getConnectedSpace() const;
		bool addPeople(IdType aPassenger, std::function<bool(const ActivityEvent&)> aActivityUpdateHandler);
		void removePeople(IdType aPassenger);

	protected:
		EventEmitter<ActivityEvent> eventEmitter;
		std::unordered_map<IdType, IdType> passengerHandlerMap;
		IdType connectedSpace;
	};
}