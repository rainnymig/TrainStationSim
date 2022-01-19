#include "passenger.h"

#include "boardingChecklist.h"

#include <set>

namespace tss
{
	Passenger::Passenger(
		const TimeUnit aSpawnTime, 
		const IdType aTargetTrain, 
		const PassengerClass aPassengerClass, 
		const bool aHasTicket)
		: spawnTime(aSpawnTime)
		, targetTrain(aTargetTrain)
		, passengerClass(aPassengerClass)
		, hasTicket(aHasTicket)
		, id(generateId())
		, activity(NULL_ID)
		, morality(100)
		, careness(100)
		, hurryness(30)
		, mobility(100)
		, age(30)
		, mood(50)
		, frustration(0)
		, hunger(10)
		, thirst(10)
		, toiletWill(10)
		, health(100)
		, entertainment(20)
	{
	}

}
