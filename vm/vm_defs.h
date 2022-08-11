#pragma once
#include <cstdint>

enum opcodes : std::int8_t
{
	NOP,
	ADD,
	SUB,
	MOV,
	PUSH,
	POP
};

enum register_operands : std::int8_t
{
	VAX_OPERAND
};