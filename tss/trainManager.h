#pragma once

#include "clock.h"
#include "id.h"
#include "train.h"

#include <memory>
#include <vector>

namespace tss
{
	class Train;
	class PassengerSpawner;

	class TrainManager
	{
	public:
		void loadSchedule(const char* aScheduleFile);
		std::vector<std::unique_ptr<PassengerSpawner>> getSpawnersFromTrain() const;
		TimeUnit getTimeToDeparture(const TimeUnit aTime, const IdType aTrainId) const;
	private:
		std::vector<Train> trains;
	};
}
