#pragma once
#include<cstdint>
#include<exception>
#include<functional>

class Chip8Cpu
{
public:
	static constexpr unsigned int NUMBER_OF_REGISTERS = 16;
	static constexpr unsigned int MEMORY_SIZE = 4096;
	static constexpr unsigned int SCREEN_WIDTH = 64;
	static constexpr unsigned int SCREEN_HIGHT = 32;
	static constexpr unsigned int STACK_CAPACITY = 24;
	static constexpr unsigned int SPRITE_WIDTH = 8;
	static constexpr unsigned int NUMBER_OF_KEYS = 16;
	static constexpr unsigned int PROGRAM_START = 0x200;

	uint8_t GPRegisters[NUMBER_OF_REGISTERS] = { 0 };
	uint8_t* RegisterF = nullptr;
	uint16_t AddressRegister = 0;
	uint16_t ProgramCounter = 0;
	uint8_t Memory[MEMORY_SIZE] = { 0 };
	bool ScreenBuffer[SCREEN_HIGHT * SCREEN_WIDTH] = { 0 };
	bool Keys[NUMBER_OF_KEYS] = { 0 };
	uint8_t DelayTimer = 0;
	uint8_t SoundTimer = 0;
	bool Jumped = false;
private:
	uint16_t _stack[STACK_CAPACITY] = { 0 };
	unsigned int _stackCurrentSize = 0;
	bool _isBlocking = false;
	uint16_t _fontsSpriteAddresses[NUMBER_OF_KEYS];
	std::function<void(Chip8Cpu&)> _onRelease = nullptr;

public:
	Chip8Cpu(uint16_t fontsSpriteAddresses[NUMBER_OF_KEYS])
	{
		for (int i = 0; i < NUMBER_OF_KEYS; i++)
		{
			_fontsSpriteAddresses[i] = fontsSpriteAddresses[i];
		}

		RegisterF = GPRegisters + NUMBER_OF_REGISTERS-1;
	}

	bool IsBlocking()const
	{
		return _isBlocking;
	}

	void Block(std::function<void(Chip8Cpu&)> onRelease)
	{
		_isBlocking = true;
		_onRelease = onRelease;
	}

	void Release()
	{
		_isBlocking = false;
		if (_onRelease != nullptr)
		{
			_onRelease(*this);
			_onRelease = nullptr;
		}
	}

	uint16_t Pop()
	{
		if (_stackCurrentSize > 0)
		{
			_stackCurrentSize--;

			return _stack[_stackCurrentSize];
		}

		throw "Stack current size is 0 or below";
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
			throw "Stack overflow";
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
			throw "no sprite for this key exist";
		}
	}
};