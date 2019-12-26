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
	static constexpr unsigned int NUMBER_OF_KEYS = 16;
	static constexpr unsigned int PROGRAM_START = 0x200;

	uint8_t GPRegisters[NUMBER_OF_REGISTERS] = { 0 };
	uint16_t AddressRegister = 0;
	uint16_t ProgramCounter = 0;
	bool FlagRegister = false;
	uint8_t Memory[MEMORY_SIZE] = { 0 };
	bool ScreenBuffer[SCREEN_HIGHT * SCREEN_WIDTH] = { 0 };
	bool Keys[NUMBER_OF_KEYS] = { 0 };
	uint8_t DelayTimer = 0;
	uint8_t SoundTimer = 0;

private:
	uint16_t _stack[STACK_CAPACITY] = { 0 };
	unsigned int _stackCurrentSize = 0;
	bool _isBlocking = false;
	uint16_t _fontsSpriteAddresses[NUMBER_OF_KEYS];

public:
	Chip8Cpu(uint16_t fontsSpriteAddresses[NUMBER_OF_KEYS])
	{
		for (int i = 0; i < NUMBER_OF_KEYS; i++)
		{
			_fontsSpriteAddresses[i] = fontsSpriteAddresses[i];
		}
	}

	void Block()
	{
		_isBlocking = true;
	}

	void Release()
	{
		_isBlocking = false;
	}

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

	uint16_t GetFontSpriteAddress(uint8_t key)
	{
		if (key < NUMBER_OF_KEYS)
		{
			return _fontsSpriteAddresses[key];
		}
		else
		{
			throw std::exception("no sprite for this key exist");
		}
	}
};