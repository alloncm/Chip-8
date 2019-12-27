#include "OpcodeRunner4BitValue.h"

OpcodeRunner4BitValue::OpcodeRunner4BitValue(Chip8Cpu & cpu, OneValueOpcodeRunner(*opcodeFuncResolverFunc)(uint8_t))
	:
	OpcodeRunner(cpu),
	_opcodeFuncResolverFunc(opcodeFuncResolverFunc)
{}

void OpcodeRunner4BitValue::operator()(uint16_t opcode)
{
	uint8_t value = (opcode & 0x0F00)/0x100;
	uint8_t resolvedValue = opcode & 0x00FF;

	OneValueOpcodeRunner func = _opcodeFuncResolverFunc(resolvedValue);
	func(Cpu, value);
}
