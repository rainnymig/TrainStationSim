#include "trainPassengerSpawner.h"

#include "passenger.h"
#include "train.h"
#include <random>

namespace tss
{
	TrainPassengerSpawner::TrainPassengerSpawner(const Train& aTrain)
		: trainId(aTrain.id)
	{
		std::random_device rd;
		std::mt19937 e(rd());
		std::uniform_real_distribution<float> uniformDist(8, 12);
		float v = uniformDist(e);
		std::normal_distribution<float> normalDist(aTrain.arrivalTime, v);
		for (size_t i = 0; i < aTrain.passengerCount; i++)
		{
			++passengerDist[std::round(normalDist(e))];
		}
	}

	std::vector<Passenger> TrainPassengerSpawner::spawn(TimeUnit aTime)
	{
		std::vector<Passenger> newPassengers;

		if (passengerDist.size() == 0)
		{
			return newPassengers;
		}

		if (aTime == passengerDist.begin()->first)
		{
			size_t newPassengerCount = passengerDist.begin()->second;
			passengerDist.erase(passengerDist.begin());
			std::generate_n(
				std::back_inserter(newPassengers), 
				newPassengerCount, 
				[aTime, this]() {
					return Passenger(aTime, trainId);
				});
		}

		return newPassengers;
	}
}