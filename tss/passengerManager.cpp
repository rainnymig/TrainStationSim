#include "passengerManager.h"

#include "passenger.h"
#include "passengerSpawner.h"
#include "station.h"
#include "id.h"

namespace tss
{
	void PassengerManager::addPassengerSpawner(std::unique_ptr<PassengerSpawner>&& aSpawner)
	{
		spawners.emplace_back(std::move(aSpawner));
	}

	void PassengerManager::addPassengerSpawners(std::vector<std::unique_ptr<PassengerSpawner>>&& aSpawners)
	{
		spawners.insert(
			spawners.end(),
			std::make_move_iterator(aSpawners.begin()),
			std::make_move_iterator(aSpawners.end())
		);
	}

	void PassengerManager::update(Station& aStation)
	{
		updateSpawnPassengers(aStation);
		updatePassengers(aStation);
	}

	void PassengerManager::updateSpawnPassengers(Station& aStation)
	{
		for (auto& spawner : spawners)
		{
			std::vector<Passenger> newPassengers = spawner->spawn(aStation.clock.getTime());
			if (newPassengers.empty())
			{
				continue;
			}
			passengers.insert(
				passengers.end(),
				std::make_move_iterator(newPassengers.begin()),
				std::make_move_iterator(newPassengers.end())
			);
		}
	}

	void PassengerManager::updatePassengers(Station& aStation)
	{
	}

}