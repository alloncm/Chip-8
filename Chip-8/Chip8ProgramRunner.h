#pragma once
#include"OpcodeRunnerResolver.h"
#include<string>

class Chip8ProgramRunner
{
public:
	Chip8ProgramRunner(Chip8Cpu& cpu, OpcodeRunnerResolver opcodeRunnerResolver);
	void LoadProgram(const std::string& programName);
	void ChipCycle();
	std::vector<std::vector<bool>> GetScreenBuffer();
	void SetInput(std::vector<bool> input);
private:
	Chip8Cpu& _cpu;
	OpcodeRunnerResolver& _opcodeRunnerResolver;
};