#pragma once
#include <cstdint>

enum opcodes : std::int8_t
{
	ADD,
	SUB,
	MOV,
	PUSH,
	POP
};

enum register_operands : std::int8_t
{
	VAX_OPERAND = 5,
	VBX_OPERAND
};