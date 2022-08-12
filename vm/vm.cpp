#include "vm.h"
#include "vm_defs.h"
#include "../lexer/lexer.h"

void vm::setup_registers()
{
	registers.vip = &code[0];
	registers.vsp = reinterpret_cast<std::uintptr_t*>(&stack[0]);
	registers.vax = 0x00000000;
	registers.vbx = 0x00000000;
}

void vm::run()
{
	// Basic sanity checks.
	if (code.empty())
		return;

	// Loop through all byte code.
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
			case opcodes::MUL:
				handle_mul();
				break;
			case opcodes::DIV:
				handle_div();
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

std::uintptr_t vm::get_number_operand(const std::int8_t offset)
{
	lexer::sliced_number sliced_number;

	sliced_number.first_quarter = *(registers.vip + offset + 1);
	sliced_number.second_quarter = *(registers.vip + offset + 2);
	sliced_number.third_quarter = *(registers.vip + offset + 3);
	sliced_number.fourth_quarter = *(registers.vip + offset + 4);
#ifdef _WIN64
	sliced_number.fith_quarter = *(registers.vip + offset + 5);
	sliced_number.sixth_quarter = *(registers.vip + offset + 6);
	sliced_number.seventh_quarter = *(registers.vip + offset + 7);
	sliced_number.eighth_quarter = *(registers.vip + offset + 8);
#endif

	return sliced_number.number;
}

void vm::handle_add()
{
	const byte register_operand = get_operands(1).at(0);
	const std::uintptr_t value_operand = get_number_operand(1);

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

	// Increment the instruction pointer by the size of both operands.
	registers.vip += sizeof(register_operand) + sizeof(value_operand);
}

void vm::handle_sub()
{
	const byte register_operand = get_operands(1).at(0);
	const std::uintptr_t value_operand = get_number_operand(1);

	// Find out what register to perform the sub instruction
	// onto using the first operand, and use the second operand
	// for the value to subtract it by.
	switch (register_operand)
	{
		case register_operands::VAX_OPERAND:
			registers.vax -= value_operand;
			std::printf("0x%p | vax = %d\n", &registers.vax, registers.vax);
			break;
		case register_operands::VBX_OPERAND:
			registers.vbx -= value_operand;
			std::printf("0x%p | vbx = %d\n", &registers.vbx, registers.vbx);
			break;
		default:
			break;
	}

	// Increment the instruction pointer by the size of both operands.
	registers.vip += sizeof(register_operand) + sizeof(value_operand);
}

void vm::handle_mul()
{
	const byte register_operand = get_operands(1).at(0);
	const std::uintptr_t value_operand = get_number_operand(1);

	// Find out what register to perform the mul instruction
	// onto using the first operand, and use the second operand
	// for the value to multiply it by.
	switch (register_operand)
	{
		case register_operands::VAX_OPERAND:
			registers.vax *= value_operand;
			std::printf("0x%p | vax = %d\n", &registers.vax, registers.vax);
			break;
		case register_operands::VBX_OPERAND:
			registers.vbx *= value_operand;
			std::printf("0x%p | vbx = %d\n", &registers.vbx, registers.vbx);
			break;
		default:
			break;
	}

	// Increment the instruction pointer by the size of both operands.
	registers.vip += sizeof(register_operand) + sizeof(value_operand);
}

void vm::handle_div()
{
	const byte register_operand = get_operands(1).at(0);
	const std::uintptr_t value_operand = get_number_operand(1);

	// Find out what register to perform the div instruction
	// onto using the first operand, and use the second operand
	// for the value to divide it by.
	switch (register_operand)
	{
		case register_operands::VAX_OPERAND:
			registers.vax /= value_operand;
			std::printf("0x%p | vax = %d\n", &registers.vax, registers.vax);
			break;
		case register_operands::VBX_OPERAND:
			registers.vbx /= value_operand;
			std::printf("0x%p | vbx = %d\n", &registers.vbx, registers.vbx);
			break;
		default:
			break;
	}

	// Increment the instruction pointer by the size of both operands.
	registers.vip += sizeof(register_operand) + sizeof(value_operand);
}

void vm::handle_mov()
{
	const byte register_operand = get_operands(1).at(0);
	const std::uintptr_t value_operand = get_number_operand(1);

	// Find out what register to perform the sub instruction
	// onto using the first operand, and use the second operand
	// for the value to subtract it by.
	switch (register_operand)
	{
		case register_operands::VAX_OPERAND:
			registers.vax = value_operand;
			std::printf("0x%p | vax = %d\n", &registers.vax, registers.vax);
			break;
		case register_operands::VBX_OPERAND:
			registers.vbx = value_operand;
			std::printf("0x%p | vbx = %d\n", &registers.vbx, registers.vbx);
			break;
		default:
			break;
	}

	// Increment the instruction pointer by the size of both operands.
	registers.vip += sizeof(register_operand) + sizeof(value_operand);
}

void vm::handle_push()
{
	const std::uintptr_t value_operand = get_number_operand(0);

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

	// Increment the instruction pointer by the size of it's operand.
	registers.vip += sizeof(register_operand);
}