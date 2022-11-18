#pragma once
#include <cmath>


namespace Dolphin
{
	namespace Struct
	{
		constexpr double pi = 3.141592653589793238462643383279502884L;

		struct Angle
		{
		private:
			double radian;

		public:
			Angle();
			Angle(double radian);
			double Radian();
			double Degree();
			void Radian(double radian);
			void Degree(double degree);
			static double ToRadian(double degree);
			static double ToDegree(double radian);
		};
	}
}