#include "clock.h"

namespace tss
{
	Clock::Clock()
		: currentTime(0)
		, lastTime(0)
		, timeRate(1)
	{
	}

	void Clock::tick()
	{
		lastTime = currentTime;
		currentTime += timeRate;
	}

	void Clock::setTime(const TimeUnit aTime)
	{
		currentTime = aTime;
		lastTime = aTime;
	}

	void Clock::setTimeRate(const int aTimeRate)
	{
		timeRate = aTimeRate;
	}

}