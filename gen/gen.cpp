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
			case lexer::token_type::MOV_OP:
				result_bytes.push_back(opcodes::MOV);
				continue;
			case lexer::token_type::PUSH_OP:
				result_bytes.push_back(opcodes::PUSH);
				continue;
			case lexer::token_type::POP_OP:
				result_bytes.push_back(opcodes::POP);
				continue;
			case lexer::token_type::VAX_REG:
				result_bytes.push_back(register_operands::VAX_OPERAND);
				continue;
			case lexer::token_type::VBX_REG:
				result_bytes.push_back(register_operands::VBX_OPERAND);
				continue;
			case lexer::token_type::NUMERIC:
				result_bytes.push_back(token.numeric_value.first_quarter);
				result_bytes.push_back(token.numeric_value.second_quarter);
				result_bytes.push_back(token.numeric_value.third_quarter);
				result_bytes.push_back(token.numeric_value.fourth_quarter);
#ifdef _WIN64
				result_bytes.push_back(token.numeric_value.fith_quarter);
				result_bytes.push_back(token.numeric_value.sixth_quarter);
				result_bytes.push_back(token.numeric_value.seventh_quarter);
				result_bytes.push_back(token.numeric_value.eighth_quarter);
#endif
				continue;
			default:
				continue;
		}
	}

	return result_bytes;
} 