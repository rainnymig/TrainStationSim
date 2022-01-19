#include "space.h"

#include "activity.h"

#include <algorithm>
#include <iterator>
#include <set>

namespace tss
{
	Space::Space(IdType aId)
		: id(aId)
	{}

	constexpr IdType Space::getId() const
	{
		return id;
	}

	constexpr SpaceType Space::getType() const
	{
		return SpaceType::normal;
	}

	void Space::addActivity(Activity&& aActivity)
	{
		activities.emplace_back(std::move(aActivity));
		sortActivities();
	}

	void Space::addActivities(std::vector<Activity>&& aActivities)
	{
		activities.insert(
			std::end(activities), 
			std::make_move_iterator(std::begin(aActivities)), 
			std::make_move_iterator(std::end(aActivities)));
		sortActivities();
	}

	void Space::calculateNextSpaces()
	{
		nextSpaces.clear();

		std::set<IdType> spaces;
		std::for_each(
			activities.begin(),
			activities.end(),
			[&spaces](const auto& act) {
				spaces.insert(act.getConnectedSpace());
			});

		std::copy(
			spaces.begin(),
			spaces.end(),
			std::back_inserter(nextSpaces)
		);

		nextSpacesCalculated = true;
	}

	std::vector<IdType> Space::getNextSpaces()
	{
		if (!nextSpacesCalculated)
		{
			calculateNextSpaces();
		}

		return nextSpaces;
	}

	std::vector<Activity> Space::getActivities()
	{
		return activities;
	}

	std::vector<Activity> Space::getActivitiesOfName(std::string_view aName)
	{
		std::vector<Activity> filteredActivities;

		std::copy_if(
			activities.begin(),
			activities.end(),
			std::back_inserter(filteredActivities),
			[aName](const auto& act) {
				return act.getType() == aName;
			});

		return filteredActivities;
	}

	void Space::sortActivities()
	{
		std::sort(
			activities.begin(),
			activities.end(),
			[](const Activity& act1, const Activity& act2) {
				return act1.getType() < act2.getType();
			});
	}
}