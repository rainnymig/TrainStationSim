#pragma once

#include "id.h"
#include "passengerState.h"
#include "activity.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <string_view>

namespace tss
{
	enum class SpaceType
	{
		normal,
		platform,
	};

	class Space
	{
	public:
		Space(IdType aId);

		IdType getId() const;

		virtual constexpr SpaceType getType() const;

		void addActivity(Activity&& aActivity);
		void addActivities(std::vector<Activity>&& aActivities);
		
		void calculateNextSpaces();
		std::vector<IdType> getNextSpaces();

		std::vector<Activity> getActivities();
		std::vector<Activity> getActivitiesOfName(std::string_view aName);

	private:
		std::vector<Activity> activities;
		IdType id;

		void sortActivities();
		bool nextSpacesCalculated = false;
		std::vector<IdType> nextSpaces;
	};
}
