#pragma once

#include "passenger.h"

#include <string>
#include <unordered_map>
#include <set>

namespace tss
{
	using BoardChecklistItemId = uint8_t;

	struct BoardChecklistItem
	{
		BoardChecklistItemId id;
		std::string name;
	};

	class BoardChecklist
	{
	public:
		BoardChecklistItemId addBoardRequirement(const std::string& aRequirement);
		void fulfillRequirementForPassenger(const BoardChecklistItemId aRequirementId, const PassengerId aPassengerId);
	private:
		std::unordered_map<BoardChecklistItemId, BoardChecklistItem> checklistItems;
		std::unordered_map<PassengerId, std::set<BoardChecklistItemId>> checklist;
	};
}
