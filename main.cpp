#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "vm/vm.h"
#include "vm/vm_defs.h"
#include "lexer/lexer.h"
#include "gen/gen.h"
#include "launch_options.hpp"

int main(int argc, char* argv[])
{
	// Setup all launch options.
	options::launch_options options{};

	for (int i = 0; i < argc; i++)
	{
		const char* current_arg = argv[i];

		// TODO: Add a check for the file input here...

		if (options.next_is_output_path)
		{
			options::output_path = current_arg;
			options.next_is_output_path = false;
		}
		else if (std::strcmp(current_arg, "-help") == 0)
		{
			std::printf("[usage]\n");
			std::printf("	virtual-machine.exe <code/binary file name> <flags>\n");
			std::printf("[flags]\n");
			std::printf("-b	Build flag, compiles the content in your inputted file.\n");
			std::printf("-d	Debug flag, skips code compilation and instead just converts it to bytecode then runs it through the VM.\n");
			std::printf("-o	Out flag, lets you specify the binary's file name after the flag.");
			return EXIT_SUCCESS;
		}
		else if (std::strcmp(current_arg, "-b") == 0)
			options.build_mode = true;
		else if (std::strcmp(current_arg, "-d") == 0)
			options.debug_mode = true;
		else if (std::strcmp(current_arg, "-o") == 0)
			options.next_is_output_path = true;
	}

	// Open file.
	const char* file_name = argv[1];
	std::ifstream file_stream(file_name);
	
	// Ensure file exists.
	if (!file_stream)
	{
		std::printf("[error] No file by the name of \"%s\" exists.\n", file_name);
		std::printf("[info] Usage:\n	virtual-machine.exe <script_name.txt> <flags>\n");
		std::printf("[info] Use '-help' for more information.");
		return EXIT_FAILURE;
	}
	
	// Convert file stream to string.
	std::stringstream file_stream_str;
	file_stream_str << file_stream.rdbuf();
	std::string code = file_stream_str.str();

	// Close the passed file.
	file_stream.close();
	
	// If build mode is on without debug mode, then we just need to compile and save the binary, no need to run anything.
	if (options.build_mode && !options.debug_mode)
	{
		// Lex the file code.
		lexer lex(code);

		// Get the lexer tokens.
		const auto& lexer_tokens = lex.get_tokens();

		// Turn the tokens into the vm's bytecode.
		const auto& byte_code = gen::generate_code(lexer_tokens);

		// Create binary output file.
		std::ofstream output_file(!options::output_path.empty() 
			? options::output_path 
			: std::string(file_name) + ".bin");
	
		// Write all byte code into the binary file.
		for (const byte current_byte : byte_code)
			output_file << current_byte;

		std::printf("[info] Build successful!\n");
	
		// Close the output file and exit.
		output_file.close();
		return EXIT_SUCCESS;
	}
	// If debug mode is on, then we straight up run the bytecode, no need to build and save it.
	else if (options.debug_mode)
	{
		// Lex the file code.
		lexer lex(code);

		// Get the lexer tokens.
		const auto& lexer_tokens = lex.get_tokens();

		// Turn the tokens into the vm's bytecode.
		const auto& byte_code = gen::generate_code(lexer_tokens);

		// Run the virtual machine with the binary's byte code.
		vm virtual_machine(byte_code);

		return EXIT_SUCCESS;
	}

	// Read the binary file into a byte array, and run it's byte code.
	std::ifstream bin_file(file_name, std::ios_base::binary | std::ios_base::ate);

	const std::size_t bin_size = bin_file.tellg();
	bin_file.seekg(0);

	const std::vector<byte> bin_byte_code(bin_size);
	bin_file.read((char*)bin_byte_code.data(), bin_size);

	// Run the virtual machine with the binary's byte code.
	vm virtual_machine(bin_byte_code);

	return EXIT_SUCCESS;
}