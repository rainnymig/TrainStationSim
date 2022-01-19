#pragma once

namespace tss
{
	using TimeUnit = long long int;

	class Clock
	{
	public:
		Clock();

		void tick();

		inline TimeUnit getTime() const { return currentTime; };
		inline TimeUnit getDeltaTime() const { return currentTime - lastTime; };
		inline TimeUnit getLastTime() const { return lastTime; };
		
		void setTime(const TimeUnit aTime);
		void setTimeRate(const int aTimeRate);

	private:
		TimeUnit currentTime;
		TimeUnit lastTime;
		int timeRate;
	};
}