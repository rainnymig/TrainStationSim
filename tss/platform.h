#pragma once

#include "space.h"
#include "id.h"

#include <string_view>

namespace tss
{
	class Platform : public Space
	{
	public:

		Platform(IdType aId, std::string_view aPlatformName);

		virtual constexpr SpaceType getType() const override;
		constexpr std::string_view getName() const;

		IdType getCurrentTrain() const;
		bool hasTrain() const;
		void arriveTrain(const IdType aTrain);
		void leaveTrain();

	private:
		std::string_view platformName;
		IdType currentTrain;
	};
}