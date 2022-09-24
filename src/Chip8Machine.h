#pragma once
#include"OpcodeRunner.h"
#include<string>
#include<array>

class Chip8Machine
{
public:
	Chip8Machine(Chip8Cpu& cpu, OpcodeRunner& opcodeRunner);
	void LoadProgram(const std::string& programName);
	void ChipCycle();
	void TimersCycle();
	std::array<bool, Chip8Cpu::SCREEN_HIGHT * Chip8Cpu::SCREEN_WIDTH> GetScreenBuffer();
	void SetInput(const std::array<bool, Chip8Cpu::NUMBER_OF_KEYS>& input);
private:
	Chip8Cpu& _cpu;
	OpcodeRunner& _opcodeRunner;
};