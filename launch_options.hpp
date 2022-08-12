#pragma once
#include <cstdint>

namespace options
{
	union launch_options
	{
		struct
		{
			bool next_arg_is_output_path : 1;
			bool build_mode : 1;
			bool debug_mode : 1;
		};

		std::uint32_t options;
	};

	std::string output_path;
}