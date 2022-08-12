#include "lexer.h"

void lexer::push_token(const token_type type, const sliced_number numeric_value)
{
	token_list.push_back({ type, numeric_value });
}

void lexer::scan_tokens()
{
	const char current_char = code[current_index];

	// Count all new lines for error details.
	if (current_char == '\n')
		new_line_count++;

	// Skip all spaces.
	if (std::isspace(current_char))
		return;

	// If current char is an alpha then we can start scanning for an operator/register token.
	if (std::isalpha(current_char))
		return scan_ops_and_regs();

	// If current char is a number then we can start scanning for a numeric value.
	if (std::isdigit(current_char))
		return scan_numerics();
}

void lexer::scan_ops_and_regs()
{
	// Save the token's starting index.
	const std::size_t start_index = current_index;

	// No need to scan for the current char since we know it's a valid character.
	current_index++;

	// Continue scanning for all following characters
	while (current_index < code.length())
	{
		// Get the currently iterated char to perform checks on.
		const char current_char = code[current_index];

		// If the current character is not alpha then we know our token ended,
		// and so we can break out of the character loop to tokenize it.
		if (!std::isalpha(current_char))
			break;

		current_index++;
	}

	current_index--;

	// We know that the last index of the token would be the current one, so we use that.
	const std::size_t end_index = current_index + 1;

	// Substr the source code by our start and end indexes.
	const std::string& token_name = code.substr(start_index, end_index - start_index);

	// Try scanning for the token name in both of our maps which contain the keywords
	// for registers aswell as operators, so we can assign the token's type.
	const auto& operator_value = operator_tokens.find(token_name);
	const auto& register_value = register_tokens.find(token_name);

	// If the token exists as a key in either maps, then we push it's value (the enum index) to the token list.
	if (operator_value != operator_tokens.end())
		return push_token(operator_value->second);
	else if (register_value != register_tokens.end())
		return push_token(register_value->second);

	// If the token doesn't exist as a key in either maps, then we know it's an invalid keyword.
	// And so we can handle the error.
	std::printf("[error@line%i] Invalid keyword \'%s\'. Skipping line %i.\n", new_line_count, token_name.c_str(), new_line_count);
	
	// Skip everything until the next code line or until the code ends.
	while (code[current_index] != '\n' && current_index != code.length())
		current_index++;
}

void lexer::scan_numerics()
{
	// Save the token's starting index.
	const std::size_t start_index = current_index;

	// No need to scan for the current char since we know it's a digit.
	current_index++;

	while (current_index < code.length())
	{
		// Get the currently iterated char to perform checks on.
		const char current_char = code[current_index];

		if (!std::isdigit(current_char))
			break;

		current_index++;
	}

	current_index--;

	// We know that the last index of the token would be the current one, so we use that.
	const std::size_t end_index = current_index + 1;

	// Substr the source code by our start and end indexes.
	const std::string numeric_value_str = code.substr(start_index, end_index);

	// Convert the numeric in the string into an integer and clamp it 0-255.
	sliced_number numeric_value;
#ifdef _WIN64
	numeric_value.number = std::stoull(numeric_value_str);
#else
	numeric_value.number = std::stoi(numeric_value_str);
#endif

	// Push the numeric value into the token list.
	push_token(token_type::NUMERIC, numeric_value);
}

std::vector<lexer::token>& lexer::get_tokens()
{
	return token_list;
}