#pragma once
#include <chrono>


namespace Dolphin
{
	namespace Utilities
	{
		class Time
		{
		private:
			static std::chrono::milliseconds msec;
			static std::chrono::seconds sec;
			static std::chrono::minutes min;
			static std::chrono::hours h;

		public:
			static void Update();

		};
	}
}
