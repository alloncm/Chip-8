#pragma once
#include"OpcodeRunner.h"

typedef void(*OneValueOpcodeRunner)(Chip8Cpu&, uint8_t);

class OpcodeRunner4BitValue :public OpcodeRunner
{
public:
	OpcodeRunner4BitValue(Chip8Cpu& cpu, OneValueOpcodeRunner(*opcodeFuncResolverFunc)(uint8_t));
	virtual void operator()(uint16_t opcode)override;
private:
	OneValueOpcodeRunner(*_opcodeFuncResolverFunc)(uint8_t);
};
