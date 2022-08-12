#pragma once
#include <unordered_map>
#include <string>
#include <vector>

typedef unsigned char byte;

class lexer
{
public:
	static enum token_type : std::int16_t
	{
		// Opcode tokens.
		ADD_OP,
		SUB_OP,
		MUL_OP,
		DIV_OP,
		MOV_OP,
		PUSH_OP,
		POP_OP,
		// Register tokens.
		VAX_REG,
		VBX_REG,
		// Other tokens.
		NUMERIC
	};

	static union sliced_number
	{
		struct
		{
			std::uint8_t first_quarter : 8;		// 0-8
			std::uint8_t second_quarter : 8;	// 8-16
			std::uint8_t third_quarter : 8;		// 16-24
			std::uint8_t fourth_quarter : 8;	// 24-32
#ifdef _WIN64
			std::uint8_t fith_quarter : 8;		// 32-40
			std::uint8_t sixth_quarter : 8;		// 40-48
			std::uint8_t seventh_quarter : 8;	// 48-56
			std::uint8_t eighth_quarter : 8;	// 56-64
#endif
		};

		// Using uintptr_t due to it's size 32/64 bits depending on the architecture.
		std::uintptr_t number;
	};

	static struct token
	{
		token_type type;
		sliced_number numeric_value;
	};
private:
	const std::unordered_map<std::string, token_type> operator_tokens =
	{
		{ "add", token_type::ADD_OP },
		{ "sub", token_type::SUB_OP },
		{ "mul", token_type::MUL_OP },
		{ "div", token_type::DIV_OP },
		{ "mov", token_type::MOV_OP },
		{ "push", token_type::PUSH_OP },
		{ "pop", token_type::POP_OP }
	};

	const std::unordered_map<std::string, token_type> register_tokens =
	{
		{ "vax", token_type::VAX_REG },
		{ "vbx", token_type::VBX_REG }
	};

	std::string code;
	std::size_t current_index = 0;
	std::size_t new_line_count = 1;
	std::vector<token> token_list;

	// Push the token into the token list.
	inline void push_token(const token_type type, const sliced_number numeric_value = { 0 });
	// Scans for all types of tokens.
	void scan_tokens();
	// Scans for operators and registers.
	void scan_ops_and_regs();
	// Scans for numeric values.
	void scan_numerics();
public:
	lexer(const std::string& text) 
		: code(text)
	{
		while (current_index < code.length())
		{
			scan_tokens();
			current_index++;
		}

		//for (const auto token : token_list)
		//{
		//	switch (token.type)
		//	{
		//		case ADD_OP:
		//			std::printf("[operator] add\n");
		//			break;
		//		case SUB_OP:
		//			std::printf("[operator] sub\n");
		//			break;
		//		case MOV_OP:
		//			std::printf("[operator] mov\n");
		//			break;
		//		case PUSH_OP:
		//			std::printf("[operator] push\n");
		//			break;
		//		case POP_OP:
		//			std::printf("[operator] pop\n");
		//			break;
		//		case VAX_REG:
		//			std::printf("[register] vax\n");
		//			break;
		//		case VBX_REG:
		//			std::printf("[register] vbx\n");
		//			break;
		//		case NUMERIC:
		//			std::printf("[numvalue] %d\n", token.numeric_value);
		//			break;
		//		default:
		//			continue;
		//	}
		//}
	}

	std::vector<token>& get_tokens();
}; 