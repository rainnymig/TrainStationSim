#pragma once

//#include "train.h"
#include "passengerSpawner.h"
#include "id.h"

#include <map>

namespace tss
{
	class Passenger;
	struct Train;

	class TrainPassengerSpawner : public PassengerSpawner
	{
	public:
		TrainPassengerSpawner(const Train& aTrain);
		virtual std::vector<Passenger> spawn(TimeUnit aTime) override;
	private:
		std::map<TimeUnit, size_t> passengerDist;
		IdType trainId;
	};
}
