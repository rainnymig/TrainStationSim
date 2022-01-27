#pragma once

#include "clock.h"
#include "passenger.h"

#include <vector>
#include <memory>

namespace tss
{
	class PassengerSpawner;
	class Station;

	class PassengerManager
	{
	public:
		void addPassengerSpawner(std::unique_ptr<PassengerSpawner>&& aSpawner);
		void addPassengerSpawners(std::vector<std::unique_ptr<PassengerSpawner>>&& aSpawners);
		void update(Station& aStation);
	private:
		std::vector<std::unique_ptr<PassengerSpawner>> spawners;
		std::vector<Passenger> passengers;

		void updateSpawnPassengers(Station& aStation);
		void updatePassengers(Station& aStation);
	};
}
