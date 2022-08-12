#pragma once
#include <cstdint>

namespace options
{
	union launch_options
	{
		struct
		{
			bool build_mode: 1;
		};

		std::uint64_t options;
	};
}