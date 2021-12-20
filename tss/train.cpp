#include "train.h"

#include "clock.h"
#include "passenger.h"

#include <algorithm>
#include <random>

namespace tss
{
	PowerType powerTypeFromString(std::string_view aString)
	{
		if (aString == "STEAM")
		{
			return PowerType::STEAM;
		}
		if (aString == "DLOC")
		{
			return PowerType::DLOC;
		}
		if (aString == "ELOC")
		{
			return PowerType::ELOC;
		}
		if (aString == "DMU")
		{
			return PowerType::DMU;
		}
		if (aString == "EMU")
		{
			return PowerType::EMU;
		}
		return PowerType::EMU;
	}

	OperationType operationTypeFromString(std::string_view aString)
	{
		if (aString == "TRAM")
		{
			return OperationType::TRAM;
		}
		if (aString == "U")
		{
			return OperationType::U;
		}
		if (aString == "S")
		{
			return OperationType::S;
		}
		if (aString == "R")
		{
			return OperationType::R;
		}
		if (aString == "RE")
		{
			return OperationType::RE;
		}
		if (aString == "IC")
		{
			return OperationType::IC;
		}
		if (aString == "ICE")
		{
			return OperationType::ICE;
		}
		return OperationType::S;
	}

	Train trainFromJson(const rapidjson::Value& aJsonValue)
	{
		assert(aJsonValue.IsObject());

		Train train{
			aJsonValue["id"].GetUint(),
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

	TrainPassengerSpawner::TrainPassengerSpawner(const Train& aTrain)
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
					return Passenger();
				});
		}

		return newPassengers;
	}
}