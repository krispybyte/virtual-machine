#pragma once
#include <Windows.h>
#include <memory>
#include <vector>

class vm
{
	struct virtual_registers
	{
		byte* vip;				// Instruction pointer, holds value of the current instruction
		std::uintptr_t* vsp;	// Stack pointer, points to a stack value

		std::uintptr_t vax;		// General purpose register
	};

	virtual_registers registers;
	byte* stack;

	void setup_registers(const byte code[]);
	void run(const byte code[], const std::size_t& code_size);
	std::vector<byte> get_operands(const std::size_t& count);
	void handle_add();
	void handle_sub();
public:
	template <typename byte_code>
	vm(const byte_code& code, const std::size_t& stack_size = 1000000)
	{
		// Allocate the vm's stack
		stack = new byte[stack_size];
		std::printf("0x%x  Allocated %i byte stack for the vm...\n", stack, stack_size);

		// Setup vm registers and run it
		setup_registers(code);
		run(code, sizeof(code));
	}

	~vm()
	{
		// Wipe the stack off of memory
		std::printf("0x%x  Deallocating vm stack...\n", stack);
		delete[] stack;
	}
};