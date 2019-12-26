#pragma once
#include"OpcodeRunner.h"
class OpcodeRunner4Bit8BitValues :public OpcodeRunner
{
private:
	void(*_opcodeFunc)(Chip8Cpu&, uint8_t, uint8_t);
public:
	OpcodeRunner4Bit8BitValues(Chip8Cpu& cpu, void(*opcodeFunc)(Chip8Cpu&, uint8_t, uint8_t));
	virtual void operator()(uint16_t opcode)override;
};

