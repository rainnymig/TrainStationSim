#pragma once

#include "id.h"
#include "space.h"

#include <vector>
#include <unordered_map>
#include <memory>

namespace tss
{
	class SpaceLayout
	{
	public:
		void addSpace(std::unique_ptr<Space>&& aSpace);
		void addSpawnPoint(const IdType aSpawnPoint);
		const Space* getRandomeSpawnPoint() const;
		Space* getSpaceOfId(const IdType aId) const;

	private:
		std::vector<IdType> spawnPoints;
		std::unordered_map<IdType, std::unique_ptr<Space>> spaces;
	};
}
