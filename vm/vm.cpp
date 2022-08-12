#include "vm.h"
#include "vm_defs.h"

void vm::setup_registers()
{
	registers.vip = const_cast<byte*>(&code[0]);
	registers.vsp = reinterpret_cast<std::uintptr_t*>(&stack[0]);
}

void vm::run()
{
	// Basic sanity checks
	if (code.empty())
		return;

	// Loop through all byte code
	for (auto i = 0; i < code.size(); i++)
	{
		const byte current_opcode = *registers.vip;

		switch (current_opcode)
		{
			case opcodes::NOP:
				continue;
			case opcodes::ADD:
				handle_add();
				break;
			case opcodes::SUB:
				handle_sub();
				break;
			default:
				break;
		}

		// Every instruction is at least a single byte,
		// so we'll be incrementing that byte in here.
		// note that some instructions expect operands,
		// we'll account for those in the handler functions.
		registers.vip++;
	}
}

std::vector<byte> vm::get_operands(const std::size_t& count)
{
	std::vector<byte> result;

	for (int i = 1; i < count + 1; i++)
		result.push_back(*(registers.vip + i));

	return result;
}

void vm::handle_add()
{
	const auto operands = get_operands(2);
	const byte register_operand = operands.at(0);
	const byte value_operand = operands.at(1);

	// Find out what register to perform the add instruction
	// onto using the first operand, and use the second operand
	// for the value to increment it by.
	switch (register_operand)
	{
		case register_operands::VAX_OPERAND:
			registers.vax += value_operand;
			std::printf("0x%p | vax = %i\n", &registers.vax, registers.vax);
			break;
		default:
			break;
	}

	// Increment the instruction pointer by the size of the two following operands.
	registers.vip += 2;
}

void vm::handle_sub()
{
	const auto operands = get_operands(2);
	const byte register_operand = operands.at(0);
	const byte value_operand = operands.at(1);

	// Find out what register to perform the sub instruction
	// onto using the first operand, and use the second operand
	// for the value to subtract it by.
	switch (register_operand)
	{
		case register_operands::VAX_OPERAND:
			registers.vax -= value_operand;
			std::printf("0x%p | vax = %i\n", &registers.vax, registers.vax);
			break;
		default:
			break;
	}

	// Increment the instruction pointer by the size of the two following operands.
	registers.vip += 2;
} 