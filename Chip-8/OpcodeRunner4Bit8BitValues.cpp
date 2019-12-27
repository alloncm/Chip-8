#include "OpcodeRunner4Bit8BitValues.h"

OpcodeRunner4Bit8BitValues::OpcodeRunner4Bit8BitValues(Chip8Cpu & cpu, void(*opcodeFunc)(Chip8Cpu &, uint8_t, uint8_t))
	:
	OpcodeRunner(cpu),
	_opcodeFunc(opcodeFunc)
{}

void OpcodeRunner4Bit8BitValues::operator()(uint16_t opcode)
{
	uint8_t first4BitValue = (opcode & 0x0F00)/0x100;
	uint8_t second8BitValue = opcode & 0x00FF;

	_opcodeFunc(Cpu, first4BitValue, second8BitValue);
}

