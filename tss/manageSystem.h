#pragma once

#include "passengerSpawner.h"
#include "stage.h"
#include "passenger.h"
#include "train.h"
#include "clock.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

namespace tss
{
	class StageManager
	{
	public:
		void addStage(const Stage& aStage);

		StageId getNextStageForPassenger(const Passenger& aPassenger) const;

	private:
		std::unordered_map<StageId, Stage> stages;
	};

	class PassengerManager
	{
	public:
		void addPassengerSpawner(std::unique_ptr<PassengerSpawner> aSpawner);
		void update(TimeUnit aTime);
	private:
		std::vector<std::unique_ptr<PassengerSpawner>> spawners;
		std::vector<Passenger> passengers;

		void updateSpawnPassengers(TimeUnit aTime);
		void updatePassengers(TimeUnit aTime, const StageManager& aStageManager);
	};

	class TrainManager
	{
	public:
		void loadSchedule(const char* aScheduleFile, PassengerManager& aPassengerManager);
	private:
		std::vector<Train> trains;
	};
}