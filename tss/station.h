#pragma once

#include "clock.h"
#include "trainManager.h"
#include "boardingChecklist.h"
#include "spaceLayout.h"

#include <memory>

namespace tss
{
	class Station
	{
	public:
		Clock clock;
		TrainManager trainManager;
		BoardingChecklist boardingChecklist;
		SpaceLayout stationLayout;
	};
}
