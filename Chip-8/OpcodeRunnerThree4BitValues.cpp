#include "OpcodeRunnerThree4BitValues.h"

OpcodeRunnerThree4BitValues::OpcodeRunnerThree4BitValues(Chip8Cpu & cpu, void(*opcodeFunc)(Chip8Cpu &, uint8_t, uint8_t, uint8_t))
	:
	OpcodeRunner(cpu),
	_opcodeFunc(opcodeFunc)
{}

void OpcodeRunnerThree4BitValues::operator()(uint16_t opcode)
{
	uint8_t firstValue = opcode & 0x0F00;
	uint8_t secondValue = opcode & 0x00F0;
	uint8_t thirdValue = opcode & 0x000F;

	_opcodeFunc(Cpu, firstValue, secondValue, thirdValue);
}
