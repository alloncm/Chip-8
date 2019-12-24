#pragma once
#include<cstdint>
#include<exception>

class Chip8Cpu
{
public:
	static constexpr unsigned int NUMBER_OF_REGISTERS = 15;
	static constexpr unsigned int MEMORY_SIZE = 4096;
	static constexpr unsigned int SCREEN_WIDTH = 64;
	static constexpr unsigned int SCREEN_HIGHT = 32;
	static constexpr unsigned int STACK_CAPACITY = 24;
	static constexpr unsigned int SPRITE_WIDTH = 8;

	uint8_t GPRegisters[NUMBER_OF_REGISTERS];
	uint16_t AddressRegister;
	uint16_t ProgramCounter;
	bool FlagRegister;
	uint8_t Memory[MEMORY_SIZE];
	bool ScreenBuffer[SCREEN_HIGHT * SCREEN_WIDTH];

private:
	uint16_t _stack[STACK_CAPACITY];
	unsigned int _stackCurrentSize = 0;

public:

	uint16_t Pop()
	{
		if (_stackCurrentSize > 0)
		{
			_stackCurrentSize--;

			return _stack[0];
		}

		throw std::exception("Stack current size is 0 or below");
	}

	void Push(uint16_t value)
	{
		if (_stackCurrentSize < STACK_CAPACITY)
		{
			_stack[_stackCurrentSize] = value;
			_stackCurrentSize++;
		}
		else
		{
			throw std::exception("Stack overflow");
		}
	}

};