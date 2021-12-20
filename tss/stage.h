#pragma once

#include <string>
#include <queue>
#include <functional>

namespace tss
{
	class Passenger;
	class Activity;

	using StageId = uint16_t;
	
	class Stage
	{
	public:
		StageId id;

		void addActivity(Activity&& aActivity);

	private:

		std::string name;
		std::vector<StageId> nextStages;
		std::vector<Activity> activities;
	};

}