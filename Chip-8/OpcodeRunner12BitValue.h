#pragma once
#include "OpcodeRunner.h"
#include"Chip8Cpu.h"
class OpcodeRunner12BitValue : public OpcodeRunner
{
private:
	void(*_opcodeFunc)(Chip8Cpu&, uint16_t);

public:
	OpcodeRunner12BitValue(void(*opcodeFunc)(Chip8Cpu&, uint16_t), Chip8Cpu& cpu);
	virtual void operator()(uint16_t opcode) override;
};

