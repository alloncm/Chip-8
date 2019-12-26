#pragma once
#include<cstdint>
#include"Chip8Cpu.h"

class OpcodeRunner
{
public:
	OpcodeRunner(Chip8Cpu& cpu)
		:
		Cpu(cpu)
	{}

	virtual void operator()(uint16_t opcode) = 0;
protected:
	Chip8Cpu& Cpu;
};

