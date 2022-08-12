#pragma once
#include <cstdint>

namespace options
{
	union launch_options
	{
		struct
		{
			bool build_mode: 1;
			bool debug_mode: 1;
		};

		std::uintptr_t options;
	};
}