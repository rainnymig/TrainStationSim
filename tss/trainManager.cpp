#include "trainManager.h"

#include "train.h"
#include "passengerManager.h"
#include "passengerSpawner.h"
#include "trainPassengerSpawner.h"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <algorithm>
#include <memory>

namespace tss
{
	Train trainFromJson(const rapidjson::Value& aJsonValue)
	{
		assert(aJsonValue.IsObject());

		Train train{
			aJsonValue["id"].GetUint(),
			aJsonValue["name"].GetString(),
			aJsonValue["arrivalTime"].GetInt(),
			aJsonValue["departureTime"].GetInt(),
			aJsonValue["platform"].GetUint(),
			aJsonValue["wagonCount"].GetUint(),
			aJsonValue["passengerCount"].GetUint(),
			aJsonValue["boardingSpeed"].GetUint(),
			powerTypeFromString(aJsonValue["powerType"].GetString()),
			operationTypeFromString(aJsonValue["operationType"].GetString()),
		};
		return train;
	}

	void TrainManager::loadSchedule(const char* aScheduleFile)
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
		trains.clear();
		trains.reserve(trainsJson.Size());
		std::for_each(
			trainsJson.begin(),
			trainsJson.end(),
			[this](const auto& t) {
				this->trains.emplace_back(trainFromJson(t));
			});
	}

	std::vector<std::unique_ptr<PassengerSpawner>> TrainManager::getSpawnersFromTrain() const
	{
		std::vector<std::unique_ptr<PassengerSpawner>> spawners;
		std::transform(
			std::begin(trains),
			std::end(trains),
			std::back_inserter(spawners),
			[](const auto& train) {
				return std::move(std::make_unique<TrainPassengerSpawner>(train));
			}
		);
		return spawners;
	}

	TimeUnit TrainManager::getTimeToDeparture(const TimeUnit aTime, const IdType aTrainId) const
	{
		auto trainIt = std::find_if(
			trains.begin(),
			trains.end(),
			[aTrainId](const auto& train) {
				return train.id == aTrainId;
			});
		assert(trainIt != trains.end());

		return trainIt->departureTime - aTime;
	}
}