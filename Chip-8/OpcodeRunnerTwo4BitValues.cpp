#include "OpcodeRunnerTwo4BitValues.h"

OpcodeRunnerTwo4BitValues::OpcodeRunnerTwo4BitValues(Chip8Cpu & cpu, OpcodeFunc(*opcodeFuncResolverFunc)(uint8_t))
	:
	OpcodeRunner(cpu),
	_opcodeFuncResolverFunc(opcodeFuncResolverFunc)
{
}

void OpcodeRunnerTwo4BitValues::operator()(uint16_t opcode)
{
	uint8_t first4BitValue = opcode & 0x0F00;
	uint8_t second4BitValue = opcode & 0x00F0;
	uint8_t opcodeSubType = opcode & 0x000F;

	OpcodeFunc func = _opcodeFuncResolverFunc(opcodeSubType);
	func(Cpu, first4BitValue, second4BitValue);
}
