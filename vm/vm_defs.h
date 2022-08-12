#pragma once
#include <cstdint>

enum opcodes : std::int8_t
{
	ADD,
	SUB,
	MUL,
	DIV,
	MOV,
	PUSH,
	POP
};

enum register_operands : std::int8_t
{
	VAX_OPERAND = 7,
	VBX_OPERAND
};