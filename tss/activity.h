#pragma once

#include "clock.h"
#include "id.h"

#include "event.h"

#include <memory>
#include <string_view>
#include <functional>
#include <unordered_map>
#include <deque>

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
		float peoplePerMinute;
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
		const ActivityData* data;
		const ActivityProcess* process;

		Activity();
		Activity(const ActivityData* aData, const ActivityProcess* aProcess, const IdType aConnectedSpace = NULL_ID);
		Activity(const Activity&) = default;
		Activity(Activity&&) = default;
		Activity& operator=(const Activity&) = default;
		Activity& operator=(Activity&&) = default;

		std::string_view getType() const;

		void update(const Station& aStation);
		size_t getPeopleCount() const;

		void setConnectedSpace(const IdType aNextSpace);
		IdType getConnectedSpace() const;
		bool canEnter(const Passenger& aPassenger, const Station& aStation) const;
		void addPeople(IdType aPassenger, std::function<bool(const ActivityEvent&)> aActivityUpdateHandler);
		void removePeople(IdType aPassenger);
		void processPeopleInTheFront(size_t aCount);

	protected:
		EventEmitter<ActivityEvent> eventEmitter;
		std::unordered_map<IdType, IdType> passengerHandlerMap;
		std::deque<IdType> passengerQueue;
		IdType connectedSpace;
	};
}