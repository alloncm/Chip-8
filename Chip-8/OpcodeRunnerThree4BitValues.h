#pragma once
#include"OpcodeRunner.h"

class OpcodeRunnerThree4BitValues :public OpcodeRunner
{
public:
	OpcodeRunnerThree4BitValues(Chip8Cpu& cpu, void(*opcodeFunc)(Chip8Cpu&, uint8_t, uint8_t, uint8_t));
	virtual void operator()(uint16_t opcode)override;
private:
	void(*_opcodeFunc)(Chip8Cpu&, uint8_t, uint8_t, uint8_t);
};