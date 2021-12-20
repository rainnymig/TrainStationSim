#pragma once

#include "stage.h"
#include "train.h"
#include "clock.h"
#include "activity.h"

#include <unordered_map>

namespace tss
{
	class StageManager;
	class Event;

	using PassengerId = unsigned long int;

	enum class PassengerState
	{
		Spawned,
		WaitingForNextStage,
		InQueue,
		FreeActivity,
		OnPlatform,
		Boarded,
	};

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
		PassengerId id;

		Passenger(
			const TimeUnit aSpawnTime, 
			const TrainId aTargetTrain = 0, 
			const PassengerClass aPassengerClass = PassengerClass::HardSeat, 
			const uint8_t aHappyness = 100);

		void Update(TimeUnit aTime, const StageManager& aStageManager);


	private:

		TimeUnit spawnTime;

		StageId stage;
		std::unordered_map<StageId, TimeUnit> stageTime;
		TimeUnit stageEnterTime;

		ActivityId activity;

		PassengerState state;
		std::unordered_map<PassengerState, TimeUnit> stateTime;

		PassengerClass passengerClass;

		TimeUnit nextActionTime;

		TrainId targetTrain;

		uint8_t happyness;

		void onActivityFinished(const Event& aEvent);
	};
}
