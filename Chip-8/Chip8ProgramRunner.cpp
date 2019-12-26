#include "Chip8ProgramRunner.h"
#include<fstream>
#include<Windows.h>

Chip8ProgramRunner::Chip8ProgramRunner(Chip8Cpu & cpu, OpcodeRunnerResolver opcodeRunnerResolver)
	:
	_cpu(cpu),
	_opcodeRunnerResolver(opcodeRunnerResolver)
{}

void Chip8ProgramRunner::LoadProgram(const std::string & programName)
{
	std::ifstream program(programName, std::ios::binary | std::ios::in);
	unsigned int counter = _cpu.PROGRAM_START;
	while (program.good())
	{
		_cpu.Memory[counter] = program.get();
		counter++;
	}

	_cpu.ProgramCounter = _cpu.PROGRAM_START;

	OutputDebugString(L"recieved program at length of " + counter - _cpu.PROGRAM_START);
}

void Chip8ProgramRunner::ChipCycle()
{
	_opcodeRunnerResolver(_cpu.ProgramCounter);
	_cpu.ProgramCounter+=sizeof(uint16_t);
}
