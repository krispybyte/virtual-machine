#pragma once
#include <vector>
#include "../lexer/lexer.h"

namespace gen
{
	typedef unsigned char byte;
	std::vector<byte> generate_code(const std::vector<lexer::token>& token_list);
}