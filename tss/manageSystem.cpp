#include "manageSystem.h"

#include <algorithm>
#include <exception>
#include <vector>
#include <string>
#include <exception>
#include <cstdio>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>


namespace tss
{
	void StageManager::addStage(const Stage& aStage)
	{
		if (stages.find(aStage.id) != stages.end())
		{
			throw std::exception("duplicate stage id");
		}

		stages.insert({aStage.id, aStage});
	}

	//void StageManager::addProcessorToStage(StageId aStageId, StageProcessor&& aStageProcessor)
	//{
	//	if (stageProcessorMap.find(aStageId) == stageProcessorMap.end())
	//	{
	//		stageProcessorMap.insert({ aStageId, {} });
	//	}

	//	stageProcessorMap[aStageId].emplace_back(aStageProcessor);
	//}

	//StageId StageManager::getNextStageForPassenger(const Passenger& aPassenger)
	//{
	//	for (auto& stageId : stages[aPassenger.stage].nextStages)
	//	{
	//		if (stages[stageId].checkEntry(aPassenger))
	//		{
	//			return stageId;
	//		}
	//	}
	//}

	//void PassengerManager::addPassengerSpawner(std::unique_ptr<PassengerSpawner> aSpawner)
	//{
	//	spawners.emplace_back(std::move(aSpawner));
	//}

	void PassengerManager::update(TimeUnit aTime)
	{
		updateSpawnPassengers(aTime);
	}

	void PassengerManager::updateSpawnPassengers(TimeUnit aTime)
	{
		static PassengerId id = 1;
		for (auto& spawner : spawners)
		{
			std::vector<Passenger> newPassengers = spawner->spawn(aTime);
			if (newPassengers.empty())
			{
				continue;
			}
			for (auto& passenger : newPassengers)
			{
				passenger.id = id++;
			};
			passengers.insert(
				passengers.end(), 
				std::make_move_iterator(newPassengers.begin()), 
				std::make_move_iterator(newPassengers.end())
			);
		}
	}

	void PassengerManager::updatePassengers(TimeUnit aTime, const StageManager& aStageManager)
	{
		for (Passenger& passenger : passengers)
		{

		}
	}

	void TrainManager::loadSchedule(const char* aScheduleFile, PassengerManager& aPassengerManager)
	{
		using namespace rapidjson;
		FILE* fp = fopen(aScheduleFile, "rb");
		char readBuffer[256];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		rapidjson::Document d;
		d.ParseStream(is);
		fclose(fp);
		if (d.HasParseError())
		{
			throw std::exception("load schedule failed");
			return;
		}

		auto trainsJson = d["trains"].GetArray();
		trains.reserve(trainsJson.Size());
		std::for_each(
			trainsJson.begin(), 
			trainsJson.end(), 
			[this](auto& t) {
				this->trains.emplace_back(trainFromJson(t));
			});

		for (auto& train : trains)
		{
			std::unique_ptr<PassengerSpawner> spawner = std::make_unique<TrainPassengerSpawner>(train);
			aPassengerManager.addPassengerSpawner(std::move(spawner));
		}
	}
}
