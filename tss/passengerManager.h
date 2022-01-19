#pragma once

#include "clock.h"

#include <vector>
#include <memory>

namespace tss
{
	class PassengerSpawner;
	class Passenger;
	class Station;

	class PassengerManager
	{
	public:
		void addPassengerSpawner(std::unique_ptr<PassengerSpawner>&& aSpawner);
		void update(Station& aStation);
	private:
		std::vector<std::unique_ptr<PassengerSpawner>> spawners;
		std::vector<Passenger> passengers;

		void updateSpawnPassengers(Station& aStation);
		void updatePassengers(Station& aStation);
	};
}
