#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "vm/vm.h"
#include "vm/vm_defs.h"
#include "lexer/lexer.h"
#include "gen/gen.h"

int main(int argc, char* argv[])
{
	//constexpr byte vm_code[]
	//{							// intel asm syntax
	//	ADD, VAX_OPERAND, 5,	// add rax, 5
	//	SUB, VAX_OPERAND, 5		// sub rax, 5
	//};
	//
	//vm virtual_machine(vm_code);
	//
	//virtual_machine.~vm();
	//return std::getchar();

	std::string code;
	
	if (argc == 1) // Text passing mode
	{
		std::printf("[VM]\nWrite code to interpret...\n");
	
		//vm virtual_machine({ NOP });

		while (true)
		{
			std::cin >> code;
	
			if (code == "exit")
				return EXIT_SUCCESS;
	
			if (!code.empty())
			{
				lexer lex(code);

				const auto& lexer_tokens = lex.get_tokens();
				const auto& byte_code = gen::generate_code(lexer_tokens);

				code.clear();
			}
		}
	}
	else if (argc == 2) // File reading mode
	{
		// Open file
		const char* file_name = argv[1];
		std::ifstream file_stream(file_name);
	
		// Ensure file exists
		if (!file_stream)
		{
			std::printf("[error] No file by the name of \"%s\" exists.\n", file_name);
			std::printf("[info] Usage:\n	1) virtual-machine.exe <script_name.txt>\n	2) virtual-machine.exe");
			return EXIT_FAILURE;
		}
	
		// Convert file stream to string
		std::stringstream file_stream_str;
		file_stream_str << file_stream.rdbuf();
		code = file_stream_str.str();
	
		// Lex the file code
		lexer lex(code);
		
		// Get the lexer tokens.
		const auto& lexer_tokens = lex.get_tokens();

		// Turn the tokens into the vm's bytecode.
		const auto& byte_code = gen::generate_code(lexer_tokens);

		// Run the virtual machine with the byte code.
		vm virtual_machine(byte_code);
	}
	
	return EXIT_SUCCESS;
}