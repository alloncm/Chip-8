#include "Chip8Machine.h"
#include<fstream>
#include<cstdio>


static void AddSprite(Chip8Cpu& cpu, int location, uint8_t sprite[5])
{
	for (int i = 0; i < 5; i++)
	{
		cpu.Memory[i + location] = sprite[i];
	}
}

Chip8Machine::Chip8Machine(Chip8Cpu& cpu, OpcodeRunner& opcodeRunner)
	:
	_cpu(cpu),
	_opcodeRunner(opcodeRunner)
{
        //digits
    uint8_t d0[]{ 0xF0,0x90,0x90,0x90,0xF0 };
    AddSprite(_cpu, 0, d0);
    uint8_t d1[]{ 0x20,0x60,0x20,0x20,0x70 };
    AddSprite(_cpu, 5, d1);
    uint8_t d2[]{ 0xF0,0x10,0xF0,0x80,0xF0 };
    AddSprite(_cpu, 10, d2);
    uint8_t d3[]{ 0xF0,0x10,0xF0,0x10,0xF0 };
    AddSprite(_cpu, 15, d3);
    uint8_t d4[]{ 0x90,0x90,0xF0,0x10,0x10 };
    AddSprite(_cpu, 20, d4);
    uint8_t d5[]{ 0xF0,0x80,0xF0,0x10,0xF0 };
    AddSprite(_cpu, 25, d5);
    uint8_t d6[]{ 0xF0,0x80,0xF0,0x90,0xF0 };
    AddSprite(_cpu, 30, d6);
    uint8_t d7[]{ 0xF0,0x10,0x20,0x40,0x40 };
    AddSprite(_cpu, 35, d7);
    uint8_t d8[]{ 0xF0,0x90,0xF0,0x90,0xF0 };
    AddSprite(_cpu, 40, d8);
    uint8_t d9[]{ 0xF0,0x90,0xF0,0x10,0xF0 };
    AddSprite(_cpu, 45, d9);
    uint8_t dA[]{ 0xF0,0x90,0xF0,0x90,0x90 };
    AddSprite(_cpu, 50, dA);
    uint8_t dB[]{ 0xE0,0x90,0xE0,0x90,0xE0 };
    AddSprite(_cpu, 55, dB);
    uint8_t dC[]{ 0xF0,0x80,0x80,0x80,0xF0 };
    AddSprite(_cpu, 60, dC);
    uint8_t dD[]{ 0xE0,0x90,0xF0,0x90,0xE0 };
    AddSprite(_cpu, 65, dD);
    uint8_t dE[]{ 0xF0,0x80,0xF0,0x80,0xF0 };
    AddSprite(_cpu, 70, dE);
    uint8_t dF[]{ 0xF0,0x80,0xF0,0x80,0x80 };
    AddSprite(_cpu, 75, dF);

}

void Chip8Machine::LoadProgram(const std::string & programName)
{
	std::ifstream program(programName, std::ios::binary | std::ios::in);
	unsigned int counter = _cpu.PROGRAM_START;
    if (!program.good())
    {
        throw "Error openning the file";
    }
	while (program.good())
	{
		_cpu.Memory[counter] = program.get();
		counter++;
	}
	_cpu.ProgramCounter = _cpu.PROGRAM_START;

	printf("recieved program at length of %d\n", counter - _cpu.PROGRAM_START);
}

void Chip8Machine::ChipCycle()
{
	if (!_cpu.IsBlocking())
	{
		uint16_t opcode = _cpu.Memory[_cpu.ProgramCounter];
		opcode <<= 8;
		opcode += _cpu.Memory[_cpu.ProgramCounter + 1];
		_opcodeRunner(opcode);
		if (!_cpu.Jumped)
		{
			_cpu.ProgramCounter += sizeof(uint16_t);
		}
		else
		{
			_cpu.Jumped = false;
		}
	}
}

void Chip8Machine::TimersCycle()
{
	if (_cpu.DelayTimer > 0)
	{
		_cpu.DelayTimer--;
	}
	if (_cpu.SoundTimer > 0)
	{
		_cpu.SoundTimer--;
	}
}

std::array<bool, Chip8Cpu::SCREEN_HIGHT * Chip8Cpu::SCREEN_WIDTH> Chip8Machine::GetScreenBuffer()
{
	std::array<bool, Chip8Cpu::SCREEN_HIGHT * Chip8Cpu::SCREEN_WIDTH> output;
	for (int i = 0; i < _cpu.SCREEN_HIGHT * _cpu.SCREEN_WIDTH; i++)
	{
        output[i] = _cpu.ScreenBuffer[i];
	}

	return output;  
}

void Chip8Machine::SetInput(const std::array<bool, Chip8Cpu::NUMBER_OF_KEYS>& input)
{
	for (int i = 0; i < _cpu.NUMBER_OF_KEYS; i++)
	{
		_cpu.Keys[i] = input[i];
		if (input[i])
		{
			if (_cpu.IsBlocking())
			{
				_cpu.Release();
			}
		}
	}
}