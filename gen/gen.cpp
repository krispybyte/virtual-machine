#include "gen.h"
#include "../vm/vm_defs.h"

typedef unsigned char byte;

std::vector<byte> gen::generate_code(const std::vector<lexer::token>& token_list)
{
	std::vector<byte> result_bytes;

	for (const auto& token : token_list)
	{
		switch (token.type)
		{
			case lexer::token_type::ADD_OP:
				result_bytes.push_back(opcodes::ADD);
				continue;
			case lexer::token_type::SUB_OP:
				result_bytes.push_back(opcodes::SUB);
				continue;
			case lexer::token_type::VAX_REG:
				result_bytes.push_back(register_operands::VAX_OPERAND);
				continue;
			case lexer::token_type::NUMERIC:
				result_bytes.push_back(token.numeric_value);
				continue;
			default:
				continue;
		}
	}

	return result_bytes;
}