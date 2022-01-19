#include "boardingChecklist.h"

#include <cassert>
#include <algorithm>
#include <iterator>

namespace tss
{
	void BoardingChecklist::addBoardRequirement(const PassengerState aRequirement)
	{
		checklistItems.insert(aRequirement);
	}

	void BoardingChecklist::fulfillRequirementForPassenger(const PassengerState aRequirementName, const IdType aPassengerId)
	{
		assert(checklistItems.contains(aRequirementName));
		checklist[aPassengerId].insert(aRequirementName);
	}

	std::unordered_set<PassengerState> BoardingChecklist::getUnfulfilledRequirementsForPassenger(const IdType aPassengerId) const
	{
		auto fulfilled = checklist.at(aPassengerId);
		std::unordered_set<PassengerState> unfulfilled;

		std::set_difference(
			checklistItems.begin(), 
			checklistItems.end(), 
			fulfilled.begin(), 
			fulfilled.end(), 
			std::inserter(unfulfilled, unfulfilled.end()));

		return unfulfilled;
	}
}