#pragma once

#include "clock.h"
#include "passengerSpawner.h"

#include <rapidjson/document.h>
#include <string_view>
#include <map>
#include <set>

namespace tss
{
	using TrainId = unsigned int;
	using PlatformId = unsigned int;

	enum class PowerType
	{
		STEAM,
		DLOC,
		ELOC,
		DMU,
		EMU,
	};

	PowerType powerTypeFromString(std::string_view aString);

	enum class OperationType
	{
		TRAM,
		U,
		S,
		R,
		RE,
		IC,
		ICE,
	};

	OperationType operationTypeFromString(std::string_view aString);

	struct Train
	{
		TrainId id;
		TimeUnit arrivalTime;
		TimeUnit departureTime;
		PlatformId platform;
		size_t wagonCount;
		size_t passengerCount;
		size_t boardingSpeed;
		PowerType powerType;
		OperationType operationType;
	};

	Train trainFromJson(const rapidjson::Value& aJsonValue);

	class TrainPassengerSpawner : public PassengerSpawner
	{
	public:
		TrainPassengerSpawner(const Train& aTrain);
		virtual std::vector<Passenger> spawn(TimeUnit aTime) override;
	private:
		std::map<TimeUnit, size_t> passengerDist;
		TrainId train;
	};
}