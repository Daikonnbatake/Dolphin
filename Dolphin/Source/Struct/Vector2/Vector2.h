#pragma once


namespace Dolphin
{
	namespace Struct
	{
		struct Vector2
		{
		private:
			float x;
			float y;


		public:
			Vector2();
			Vector2(float x, float y);
			float X();
			float Y();
			void X(float x);
			void Y(float y);
		};
	}
}