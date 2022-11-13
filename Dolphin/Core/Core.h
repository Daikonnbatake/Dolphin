#pragma once

#include <vector>
#include <string>
#include <typeinfo>

namespace Dolphin
{
	namespace Core
	{
		#define C Dolphin::Core
		#define FOR(index, maxCount) for(int i = 0, i < n; ++i)
		#define FOREACH(element, iterable) for(auto* element : iterable)
		#define RELEASE(target) if (target != nullptr) { delete[] target; target = nullptr; }

		using std::string;
		using std::vector;
		using namespace Dolphin;
		using namespace Dolphin::Core;
	}
}
