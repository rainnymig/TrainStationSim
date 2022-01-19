#pragma once

#include "id.h"

namespace tss
{
	class Space;

	class SpaceLayout
	{
	public:
		void addSpace(Space&& aSpace);
		IdType getNextSpaceId(const IdType aThisSpace) const;
		const Space& getNextSpace(const IdType aThisSpace) const;
	};
}
