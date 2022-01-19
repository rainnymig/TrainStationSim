#include "train.h"

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
}