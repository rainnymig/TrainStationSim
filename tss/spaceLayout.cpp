#include "spaceLayout.h"

#include <exception>
#include <random>
#include <algorithm>

namespace tss
{
	void SpaceLayout::addSpace(std::unique_ptr<Space>&& aSpace)
	{
		const IdType id = aSpace->getId();
		spaces[id] = std::move(aSpace);
	}

	void SpaceLayout::addSpawnPoint(const IdType aSpawnPoint)
	{
		if (std::find(spawnPoints.begin(), spawnPoints.end(), aSpawnPoint) != spawnPoints.end())
		{
			spawnPoints.push_back(aSpawnPoint);
		}
	}

	const Space* SpaceLayout::getRandomeSpawnPoint() const
	{
		if (spawnPoints.empty() || spaces.empty())
		{
			throw std::exception("can not find place to spawn.");
		}

		static std::random_device rd;
		static std::mt19937 e(rd());
		std::uniform_int_distribution<int> dist(0, spawnPoints.size() - 1);

		return spaces.at(spawnPoints[dist(e)]).get();
	}

	Space* SpaceLayout::getSpaceOfId(const IdType aId) const
	{
		return spaces.at(aId).get();
	}

}
