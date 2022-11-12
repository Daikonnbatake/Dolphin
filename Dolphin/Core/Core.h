#pragma once

#include <vector>
#include "ReadOnly.h"

namespace Dolphin
{
	namespace Core
	{
		#define C Dolphin::Core
		#define FOR(index, maxCount) for(int i = 0, i < n; ++i)
		#define FOREACH(element, iterable) for(const auto& element : iterable)

		using std::vector;
		using namespace Dolphin;
		using namespace Dolphin::Core;
		using namespace Dolphin::Helper;
	}
}
