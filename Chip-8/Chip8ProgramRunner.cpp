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
	if (!_cpu.IsBlocking())
	{
		uint16_t opcode = _cpu.Memory[_cpu.ProgramCounter];
		opcode <<= 8;
		opcode += _cpu.Memory[_cpu.ProgramCounter + 1];
		_opcodeRunnerResolver(opcode);
		_cpu.ProgramCounter += sizeof(uint16_t);
	}
	if (_cpu.DelayTimer > 0)
	{
		_cpu.DelayTimer--;
	}
	if (_cpu.SoundTimer > 0)
	{
		_cpu.SoundTimer--;
	}
}

std::vector<std::vector<bool>> Chip8ProgramRunner::GetScreenBuffer()
{
	std::vector<std::vector<bool>> output(_cpu.SCREEN_HIGHT);
	for (int i = 0; i < _cpu.SCREEN_HIGHT; i++)
	{
		output[i].resize(_cpu.SCREEN_WIDTH);
		for (int j = 0; j < _cpu.SCREEN_WIDTH; j++)
		{
			output[i][j] = _cpu.ScreenBuffer[i*_cpu.SCREEN_WIDTH+j];
		}
	}

	return output;
}

void Chip8ProgramRunner::SetInput(std::vector<bool> input)
{
	memcpy(_cpu.Keys, input.begin()._Myptr, _cpu.NUMBER_OF_KEYS);
}