#pragma once

#include "id.h"
#include "passengerState.h"

#include <unordered_map>
#include <unordered_set>

namespace tss
{
	class BoardingChecklist
	{
	public:
		void addBoardRequirement(const PassengerState aRequirement);
		void fulfillRequirementForPassenger(const PassengerState aRequirementId, const IdType aPassengerId);
		std::unordered_set<PassengerState> getUnfulfilledRequirementsForPassenger(const IdType aPassengerId) const;
	private:
		std::unordered_set<PassengerState> checklistItems;
		std::unordered_map<IdType, std::unordered_set<PassengerState>> checklist;
	};
}
