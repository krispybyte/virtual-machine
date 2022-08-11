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
		// Opcodes
		ADD_OP,
		// Registers
		VAX_REG,
		// Other
		NUMERIC
	};

	static struct token
	{
		token_type type;
		int numeric_value;
	};
private:
	const std::unordered_map<std::string, token_type> operator_tokens =
	{
		{ "add", token_type::ADD_OP }
	};

	const std::unordered_map<std::string, token_type> register_tokens =
	{
		{ "vax", token_type::VAX_REG }
	};

	std::string code;
	std::size_t current_index = 0;
	std::size_t new_line_count = 1;
	std::vector<token> token_list;

	// Push the token into the token list.
	inline void push_token(const token_type type, const int numeric_value = 0);
	// Scans for all types of tokens.
	void scan_tokens();
	// Scans for operators and registers.
	void scan_ops_and_regs();
	// Scans for numeric values.
	void scan_numerics();
	// Scans for comments and removes them from the code.
	void scan_comments();
public:
	lexer(const std::string& text) 
		: code(text)
	{
		while (current_index < code.length())
		{
			scan_tokens();
			current_index++;
		}

		for (const auto token : token_list)
		{
			switch (token.type)
			{
				case ADD_OP:
					std::printf("[operator] add\n");
					break;
				case VAX_REG:
					std::printf("[register] vax\n");
					break;
				case NUMERIC:
					std::printf("[numeric] %i\n", token.numeric_value);
					break;
				default:
					continue;
			}
		}
	}

	std::vector<token>& get_tokens();
};