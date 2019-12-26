#include "OpcodeRunnerNoValues.h"

OpcodeRunnerNoValues::OpcodeRunnerNoValues(Chip8Cpu & cpu, NoValuesOpcodeFunc(*opcodeFuncResolverFunc)(uint8_t))
	:
	OpcodeRunner(cpu),
	_opcodeFuncResolverFunc(opcodeFuncResolverFunc)
{}

void OpcodeRunnerNoValues::operator()(uint16_t opcode)
{
	uint8_t resolvedValue = opcode & 0x000F;
	NoValuesOpcodeFunc opcodeFunc = _opcodeFuncResolverFunc(resolvedValue);
	opcodeFunc(Cpu);
}
