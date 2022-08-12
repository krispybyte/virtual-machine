#include "vm.h"
#include "vm_defs.h"

void vm::setup_registers()
{
	registers.vip = &code[0];
	registers.vsp = &stack[0];
	registers.vax = 0x00000000;
	registers.vbx = 0x00000000;
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
			case opcodes::ADD:
				handle_add();
				break;
			case opcodes::SUB:
				handle_sub();
				break;
			case opcodes::MOV:
				handle_mov();
				break;
			case opcodes::PUSH:
				handle_push();
				break;
			case opcodes::POP:
				handle_pop();
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
		case register_operands::VBX_OPERAND:
			registers.vbx += value_operand;
			std::printf("0x%p | vbx = %i\n", &registers.vbx, registers.vbx);
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
		case register_operands::VBX_OPERAND:
			registers.vbx -= value_operand;
			std::printf("0x%p | vbx = %i\n", &registers.vbx, registers.vbx);
			break;
		default:
			break;
	}

	// Increment the instruction pointer by the size of the two following operands.
	registers.vip += 2;
}

void vm::handle_mov()
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
			registers.vax = value_operand;
			std::printf("0x%p | vax = %i\n", &registers.vax, registers.vax);
			break;
		case register_operands::VBX_OPERAND:
			registers.vbx = value_operand;
			std::printf("0x%p | vbx = %i\n", &registers.vbx, registers.vbx);
			break;
		default:
			break;
	}

	// Increment the instruction pointer by the size of the two following operands.
	registers.vip += 2;
}

void vm::handle_push()
{
	const byte value_operand = get_operands(1).at(0);

	// Increment the stack pointt before pushing the data.
	registers.vsp++;

	// Save the data in the byte the current stack pointer is holding.
	memcpy(registers.vsp, &value_operand, sizeof(value_operand));

	// Increment the instruction pointer by the size of the pushed data.
	registers.vip += sizeof(value_operand);
}

void vm::handle_pop()
{
	const byte register_operand = get_operands(1).at(0);

	// Find the register to pop the data onto using the instruction operand.
	switch (register_operand)
	{
		case register_operands::VAX_OPERAND:
			registers.vax = *registers.vsp;
			std::printf("0x%p | popped %i onto vax\n", &registers.vax, registers.vax);
			break;
		case register_operands::VBX_OPERAND:
			registers.vbx = *registers.vsp;
			std::printf("0x%p | popped %i onto vbx\n", &registers.vbx, registers.vbx);
			break;
		default:
			break;
	}

	// Decrement the stack pointer after popping off the data.
	registers.vsp--;

	// Increment the instruction pointer by the size of the operand (1 byte).
	registers.vip++;
}