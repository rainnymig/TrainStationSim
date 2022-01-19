#pragma once

#include "clock.h"
#include "id.h"

#include <vector>

namespace tss
{
	class Train;
	class PassengerManager;

	class TrainManager
	{
	public:
		void loadSchedule(const char* aScheduleFile, PassengerManager* aPassengerManager);
		TimeUnit getTimeToDeparture(const TimeUnit aTime, const IdType aTrainId) const;
	private:
		std::vector<Train> trains;
	};
}
