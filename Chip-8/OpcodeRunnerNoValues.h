#pragma once

#include"OpcodeRunner.h"

typedef void(*NoValuesOpcodeFunc)(Chip8Cpu&);

class OpcodeRunnerNoValues :public OpcodeRunner
{
public:
	OpcodeRunnerNoValues(Chip8Cpu& cpu, NoValuesOpcodeFunc(*opcodeFuncResolverFunc)(uint8_t));
	virtual void operator()(uint16_t opcode)override;
private:
	NoValuesOpcodeFunc (*_opcodeFuncResolverFunc)(uint8_t);
};