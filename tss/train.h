#pragma once

#include "clock.h"
#include "passengerSpawner.h"
#include "id.h"

#include <rapidjson/document.h>
#include <string_view>
#include <map>
#include <set>

namespace tss
{

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
		IdType id;
		std::string_view name;
		TimeUnit arrivalTime;
		TimeUnit departureTime;
		IdType platform;
		size_t wagonCount;
		size_t passengerCount;
		size_t boardingSpeed;
		PowerType powerType;
		OperationType operationType;
	};
}