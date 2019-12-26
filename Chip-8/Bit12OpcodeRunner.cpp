#include "OpcodeRunner12BitValue.h"

OpcodeRunner12BitValue::OpcodeRunner12BitValue(void(*opcodeFunc)(Chip8Cpu &, uint16_t), Chip8Cpu& cpu)
	:
	OpcodeRunner(cpu),
	_opcodeFunc(opcodeFunc)
{}

void OpcodeRunner12BitValue::operator()(uint16_t opcode)
{
	uint16_t value = opcode & 0x0FFF;
	_opcodeFunc(Cpu, value);
}
