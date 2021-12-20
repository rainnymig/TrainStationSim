#include "passenger.h"

#include "manageSystem.h"

namespace tss
{
	Passenger::Passenger(const TimeUnit aSpawnTime, const TrainId aTargetTrain, const PassengerClass aPassengerClass, const uint8_t aHappyness)
		: spawnTime(aSpawnTime)
		, targetTrain(aTargetTrain)
		, happyness(aHappyness)
		, nextActionTime(0)
		, stage(0)
		, passengerClass(aPassengerClass)
	{
	}

	void Passenger::Update(TimeUnit aTime, const StageManager& aStageManager)
	{
		if (state == PassengerState::Spawned || state == PassengerState::WaitingForNextStage)
		{
			stage == aStageManager.getNextStageForPassenger(*this);
		}
	}

}
