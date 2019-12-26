#pragma once
#include "OpcodeRunner.h"

typedef void(*OpcodeFunc)(Chip8Cpu&, uint8_t, uint8_t);

class OpcodeRunnerTwo4BitValues :public OpcodeRunner
{
public:
	OpcodeRunnerTwo4BitValues(Chip8Cpu& cpu, OpcodeFunc(*opcodeFuncResolverFunc)(uint8_t));

	virtual void operator()(uint16_t opcode)override;

private:
	OpcodeFunc(*_opcodeFuncResolverFunc)(uint8_t);
};