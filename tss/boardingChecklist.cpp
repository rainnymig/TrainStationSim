#include "boardingChecklist.h"

#include <cassert>

namespace tss
{
	BoardChecklistItemId BoardChecklist::addBoardRequirement(const std::string& aRequirement)
	{
		static BoardChecklistItemId id = 1;

		BoardChecklistItem item{ .id = id, .name = aRequirement };
		checklistItems[id] = item;
		id++;
		return item.id;
	}

	void BoardChecklist::fulfillRequirementForPassenger(const BoardChecklistItemId aRequirementId, const PassengerId aPassengerId)
	{
		assert(checklistItems.contains(aRequirementId));

		checklist[aPassengerId].insert(aRequirementId);
	}
}