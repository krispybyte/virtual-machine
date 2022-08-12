#pragma once
#include <Windows.h>
#include <memory>
#include <vector>

class vm
{
	struct virtual_registers
	{
		byte* vip;				// Instruction pointer, holds value of the current instruction.
		std::uintptr_t* vsp;	// Stack pointer, points to a stack value.

		std::uintptr_t vax;		// General purpose register.
		std::uintptr_t vbx;		// General purpose register.
	};

	std::vector<byte> code;
	virtual_registers registers;
	byte* stack;

	void setup_registers();
	void run();
	std::vector<byte> get_operands(const std::size_t& count);
	std::uintptr_t get_number_operand(const std::int8_t offset);
	void handle_add();
	void handle_sub();
	void handle_mov();
	void handle_push();
	void handle_pop();
public:
	vm(const std::vector<byte>& code, const std::size_t& stack_size = 4096)
		: code(code)
	{
		// Allocate the vm's stack.
		stack = new byte[stack_size];
		std::printf("0x%p | Allocated a %i byte stack for the vm...\n", stack, stack_size);

		// Setup vm registers and run it.
		setup_registers();
		run();
	}

	~vm()
	{
		// Wipe the stack off of memory.
		std::printf("0x%p | Deallocating vm stack...\n", stack);
		delete[] stack;
	}
};