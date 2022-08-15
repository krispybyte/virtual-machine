#pragma once
#include <cstdint>

enum opcodes : std::uint8_t
{
	ADD,
	SUB,
	MUL,
	DIV,
	MOV,
	PUSH,
	POP
};

enum register_operands : std::uint8_t
{
	VAX_OPERAND = 7,
	VBX_OPERAND
};