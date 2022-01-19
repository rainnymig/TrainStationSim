#include "platform.h"

#include "id.h"
#include "activity.h"

#include <exception>

namespace tss
{
	Platform::Platform(IdType aId, std::string_view aPlatformName)
		: Space(aId)
		, platformName(aPlatformName)
		, currentTrain(NULL_ID)
	{
	}

	constexpr SpaceType Platform::getType() const
	{
		return SpaceType::platform;
	}

	constexpr std::string_view Platform::getName() const
	{
		return platformName;
	}

	IdType Platform::getCurrentTrain() const
	{
		return currentTrain;
	}

	bool Platform::hasTrain() const
	{
		return currentTrain != NULL_ID;
	}

	void Platform::arriveTrain(const IdType aTrain)
	{
		if (hasTrain())
		{
			throw std::exception("train trying to enter occupied platform!");
		}

		currentTrain = aTrain;
	}

	void Platform::leaveTrain()
	{
		currentTrain = NULL_ID;
	}
}
