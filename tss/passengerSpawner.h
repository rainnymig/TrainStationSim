#pragma once
#include "clock.h"

#include <vector>

namespace tss
{
	class Passenger;

	class PassengerSpawner
	{
	public:
		virtual std::vector<Passenger> spawn(TimeUnit aTime) = 0;
		virtual ~PassengerSpawner() {};
	};
}
