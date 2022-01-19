#pragma once

#include "train.h"
#include "activity.h"
#include "id.h"

#include <unordered_map>

namespace tss
{
	class Event;
	class Station;

	enum class PassengerClass
	{
		NoSeat,
		HardSeat,
		SoftSeat,
		HardSleeper,
		SoftSleeper,
	};

	class Passenger
	{
	public:
		IdType id;

		Passenger(
			const TimeUnit aSpawnTime, 
			const IdType aTargetTrain = 0,
			const PassengerClass aPassengerClass = PassengerClass::HardSeat,
			const bool aHasTicket = true);

		void update(Station* aStation);

	private:

		TimeUnit spawnTime;

		IdType activity;

		uint8_t morality;
		uint8_t careness;
		uint8_t hurryness;
		uint8_t mobility;
		uint8_t age;

		float mood;
		float frustration;
		float hunger;
		float thirst;
		float toiletWill;
		float health;
		float entertainment;

		PassengerClass passengerClass;
		IdType targetTrain;
		bool hasTicket;

		void findNextActivity(Station* aStation);

	};
}
