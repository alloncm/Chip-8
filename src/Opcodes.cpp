#include"Opcodes.h"
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<string>
#include<bitset>

static void CheckValidAddress(const Chip8Cpu& cpu, uint16_t address)
{
	if (address > cpu.MEMORY_SIZE)
	{
		throw "Memory out of bounds address at " + address;
	}
}

static void CheckForValidRegister(const Chip8Cpu& cpu, uint8_t registerIndex)
{
	if (registerIndex >= cpu.NUMBER_OF_REGISTERS)
	{
		throw "Register is out of bounds " + registerIndex;
	}
}

static void SkipIfTrue(Chip8Cpu& cpu, bool condition)
{
	if (condition)
	{
		cpu.ProgramCounter += sizeof(uint16_t);
	}
}

static uint8_t CheckFor8BitCarry(int16_t value)
{
	return value > UINT8_MAX || value < 0 ? 1 : 0;
}

static uint8_t CheckFor8BitBorrow(int16_t value)
{
	return value > UINT8_MAX || value < 0 ? 0 : 1;
}

static void CheckForValid4BitValue(uint8_t value)
{
	if (value > 0xF)
	{
		throw "value is bigger than 0xF";
	}
}

inline static uint8_t GetFirstRegister(uint16_t opcode)
{
    return (opcode & 0x0F00) >> 8;
}

inline static uint8_t Get8BitValue(uint16_t opcode)
{
    return opcode & 0xFF;
}

inline static uint8_t GetSecondRegister(uint16_t opcode)
{
    return (opcode & 0x00F0) >> 4;
}

inline static uint16_t Get12BitValue(uint16_t opcode)
{
    return opcode & 0x0FFF;
}

void ClearScreen(Chip8Cpu& cpu)
{
	std::memset(cpu.ScreenBuffer, 0, cpu.SCREEN_HIGHT * cpu.SCREEN_WIDTH);
}

void ReturnFronSubroutine(Chip8Cpu& cpu)
{
	uint16_t address = cpu.Pop();
	cpu.ProgramCounter = address;
}

void Jump(Chip8Cpu& cpu, uint16_t opcode)
{
    uint16_t address = Get12BitValue(opcode);
	CheckValidAddress(cpu, address);

	cpu.ProgramCounter = address;
	cpu.Jumped = true;
}

void CallSubRoutine(Chip8Cpu& cpu, uint16_t opcode)
{
    uint16_t address = Get12BitValue(opcode);
	CheckValidAddress(cpu, address);

	cpu.Push(cpu.ProgramCounter);
	cpu.ProgramCounter = address;
	cpu.Jumped = true;
}

void SkipIfRegisterEqualValue(Chip8Cpu& cpu, uint16_t opcode)
{
    uint8_t registerIndex = GetFirstRegister(opcode);
    uint8_t value = Get8BitValue(opcode);
	CheckForValidRegister(cpu, registerIndex);

	SkipIfTrue(cpu, cpu.GPRegisters[registerIndex] == value);
}

void SkipIfRegisterNotEqualValue(Chip8Cpu& cpu, uint16_t opcode)
{
    uint8_t registerIndex = GetFirstRegister(opcode);
    uint8_t value = Get8BitValue(opcode);
	CheckForValidRegister(cpu, registerIndex);

	SkipIfTrue(cpu, cpu.GPRegisters[registerIndex] != value);
}

void SkipIfRegisterEqualRegister(Chip8Cpu& cpu, uint16_t opcode)
{
    uint8_t registerXIndex = GetFirstRegister(opcode);
    uint8_t registerYIndex = GetSecondRegister(opcode);
	CheckForValidRegister(cpu, registerXIndex);
	CheckForValidRegister(cpu, registerYIndex);

	SkipIfTrue(cpu, cpu.GPRegisters[registerXIndex] == cpu.GPRegisters[registerYIndex]);
}

void SetRegisterByValue(Chip8Cpu& cpu, uint16_t opcode)
{
    uint8_t registerIndex = GetFirstRegister(opcode);
	CheckForValidRegister(cpu, registerIndex);
	cpu.GPRegisters[registerIndex] = Get8BitValue(opcode);
}

void AddValueToRegisterWithoutCarry(Chip8Cpu& cpu, uint16_t opcode)
{
    uint8_t registerIndex = GetFirstRegister(opcode);
	CheckForValidRegister(cpu, registerIndex);
	cpu.GPRegisters[registerIndex] += Get8BitValue(opcode);
}

void AssignRegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndex)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, sourceRegisterIndex);

	cpu.GPRegisters[destRegisterIndex] = cpu.GPRegisters[sourceRegisterIndex];
}

void SetsRegisterToRegisterORRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndex)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, sourceRegisterIndex);

	cpu.GPRegisters[destRegisterIndex] |= cpu.GPRegisters[sourceRegisterIndex];
}

void SetsRegisterToRegisterANDRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, sourceRegisterIndedx);

	cpu.GPRegisters[destRegisterIndex] &= cpu.GPRegisters[sourceRegisterIndedx];
}

void SetsRegisterToRegisterXORRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, sourceRegisterIndedx);

	cpu.GPRegisters[destRegisterIndex] ^= cpu.GPRegisters[sourceRegisterIndedx];
}

void AddRegisterToRegisterWithCarry(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, sourceRegisterIndedx);

	int16_t tempReg = (int16_t)cpu.GPRegisters[destRegisterIndex];
	cpu.GPRegisters[destRegisterIndex] += cpu.GPRegisters[sourceRegisterIndedx];

	tempReg += cpu.GPRegisters[sourceRegisterIndedx];
	*cpu.RegisterF = CheckFor8BitCarry(tempReg);
}

void SubtractRegisterFromRegisterWithCarry(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, sourceRegisterIndedx);

	int16_t tempReg = (int16_t)cpu.GPRegisters[destRegisterIndex];
	cpu.GPRegisters[destRegisterIndex] -= cpu.GPRegisters[sourceRegisterIndedx];

	tempReg -= cpu.GPRegisters[sourceRegisterIndedx];
	*cpu.RegisterF = CheckFor8BitBorrow(tempReg);
}

void ShiftRightBy1RegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t outputRegisterIndedx)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, outputRegisterIndedx);

	*cpu.RegisterF = cpu.GPRegisters[destRegisterIndex] & 0b00000001;
	cpu.GPRegisters[destRegisterIndex] >>= 1;
}

void AssignRegisterXRegisterYMinusRegisterX(Chip8Cpu& cpu, uint8_t xRegisterIndex, uint8_t yRegisterIndex)
{
	CheckForValidRegister(cpu, xRegisterIndex);
	CheckForValidRegister(cpu, yRegisterIndex);

	int16_t temp = (int16_t)cpu.GPRegisters[yRegisterIndex];
	temp -= cpu.GPRegisters[xRegisterIndex];

	cpu.GPRegisters[xRegisterIndex] = cpu.GPRegisters[yRegisterIndex] - cpu.GPRegisters[xRegisterIndex];

	*cpu.RegisterF = CheckFor8BitBorrow(temp);
}

void ShiftLeftBy1RegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t outputRegisterIndedx)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, outputRegisterIndedx);

	std::bitset<8> bits(cpu.GPRegisters[destRegisterIndex]);
	*cpu.RegisterF = (cpu.GPRegisters[destRegisterIndex] & 0b10000000)>>7;
	cpu.GPRegisters[destRegisterIndex] <<= 1;
}

void SkipIfRegisterNotEqualRegister(Chip8Cpu& cpu, uint16_t opocde)
{
    uint8_t registerXIndex = GetFirstRegister(opocde);
    uint8_t registerYIndex = GetSecondRegister(opocde);
	CheckForValidRegister(cpu, registerXIndex);
	CheckForValidRegister(cpu, registerYIndex);

	SkipIfTrue(cpu, cpu.GPRegisters[registerXIndex] != cpu.GPRegisters[registerYIndex]);
}

void SetAddressRegister(Chip8Cpu& cpu, uint16_t opcode)
{
    uint16_t value = Get12BitValue(opcode);
	CheckValidAddress(cpu, value);

	cpu.AddressRegister = value;
}

void JumpToFirstRegisterPlusValue(Chip8Cpu& cpu, uint16_t opcode)
{
	uint16_t address = cpu.GPRegisters[0] + Get12BitValue(opcode);
	CheckValidAddress(cpu, address);

	cpu.ProgramCounter = address;
	cpu.Jumped = true;
}

void AssignRegisterRandANDValue(Chip8Cpu& cpu, uint16_t opcode)
{
    uint8_t registerIndex = GetFirstRegister(opcode);
	CheckForValidRegister(cpu, registerIndex);

	srand((unsigned int)time(NULL));
	uint8_t randomNumber = rand() % UINT8_MAX;
	cpu.GPRegisters[registerIndex] = randomNumber & Get8BitValue(opcode);
}

void DrawSprite(Chip8Cpu& cpu, uint16_t opcode)
{
    uint8_t xRegisterIndex = GetFirstRegister(opcode);
    uint8_t yRegisterIndex = GetSecondRegister(opcode);
    uint8_t height = (uint8_t)(opcode & 0x000F);
	CheckForValidRegister(cpu, xRegisterIndex);
	CheckForValidRegister(cpu, yRegisterIndex);
	if (height > 0xF)
	{
		throw "height is bigger than 0xF" + height;
	}

	bool flliped = false;
	uint16_t addressTemp = cpu.AddressRegister;
	for (int i = 0; i < height; i++)
	{
		int y = i + cpu.GPRegisters[yRegisterIndex];
		if (y < 0)
		{
			y += cpu.SCREEN_HIGHT;
		}
		else if (y >= cpu.SCREEN_HIGHT)
		{
			y -= cpu.SCREEN_HIGHT;
		}
		uint8_t v = cpu.Memory[addressTemp];
		addressTemp++;
		std::bitset<8> bits(v);
		for (int j = 0; j < cpu.SPRITE_WIDTH; j++)
		{
			int x = j + cpu.GPRegisters[xRegisterIndex];
			if (x < 0)
			{
				x += cpu.SCREEN_WIDTH;
			}
			else if (x >= cpu.SCREEN_WIDTH)
			{
				x -= cpu.SCREEN_WIDTH;
			}
			if (bits[7-j])
			{
				cpu.ScreenBuffer[cpu.SCREEN_WIDTH * y + x] = !cpu.ScreenBuffer[cpu.SCREEN_WIDTH * y + x];
				if (!cpu.ScreenBuffer[cpu.SCREEN_WIDTH * y + x])
				{
					flliped = true;
				}
			}
		}
	}

	*cpu.RegisterF = flliped ? 1 : 0;
}

void SkipIfKeyInRegisterPressed(Chip8Cpu& cpu, uint8_t registerIndex)
{
	CheckForValidRegister(cpu, registerIndex);
	uint8_t keyValue = cpu.GPRegisters[registerIndex];
	CheckForValid4BitValue(keyValue);

	SkipIfTrue(cpu, cpu.Keys[keyValue]);
}

void SkipIfKeyInRegisterNotPressed(Chip8Cpu& cpu, uint8_t registerIndex)
{
	CheckForValidRegister(cpu, registerIndex);
	uint8_t keyValue = cpu.GPRegisters[registerIndex];
	CheckForValid4BitValue(keyValue);

	SkipIfTrue(cpu, !cpu.Keys[keyValue]);
}

void SetRegisterToDelayTimer(Chip8Cpu& cpu, uint8_t registerIndex)
{
	CheckForValidRegister(cpu, registerIndex);

	cpu.GPRegisters[registerIndex] = cpu.DelayTimer;
}

void BlockKeyIsPressedAndAssignItToRegister(Chip8Cpu& cpu, uint8_t registerIndex)
{
	CheckForValidRegister(cpu, registerIndex);
	auto onReleaseLambda = [registerIndex](Chip8Cpu& chipCpu) 
	{
		bool found = false;
		uint8_t i = 0;
		while (i < chipCpu.NUMBER_OF_KEYS && !found)
		{
			if (chipCpu.Keys[i])
			{
				found = true;
			}
			else
			{
				i++;
			}
		}

		chipCpu.GPRegisters[registerIndex] = i;
	};

	cpu.Block(onReleaseLambda);
}

void SetDelayTimerToRegister(Chip8Cpu& cpu, uint8_t registerIndex)
{
	CheckForValidRegister(cpu, registerIndex);

	cpu.DelayTimer = cpu.GPRegisters[registerIndex];
}

void SetSoundTimerToRegister(Chip8Cpu& cpu, uint8_t registerIndex)
{
	CheckForValidRegister(cpu, registerIndex);

	cpu.SoundTimer = cpu.GPRegisters[registerIndex];
}

void AddRegisterToAdressRegister(Chip8Cpu& cpu, uint8_t registerIndex)
{
	CheckForValidRegister(cpu, registerIndex);

	cpu.AddressRegister += cpu.GPRegisters[registerIndex];
	*cpu.RegisterF = cpu.AddressRegister > cpu.MEMORY_SIZE ? 1 : 0;
}

void SetsAddressRegisterToFontSpriteAtRegister(Chip8Cpu& cpu, uint8_t registerIndex)
{
	CheckForValidRegister(cpu, registerIndex);

	cpu.AddressRegister = cpu.GetFontSpriteAddress(cpu.GPRegisters[registerIndex]);
}

void StoreASCIIInMemory(Chip8Cpu& cpu, uint8_t registerIndex)
{
	CheckForValidRegister(cpu, registerIndex);

	uint8_t vx = cpu.GPRegisters[registerIndex];
	cpu.Memory[cpu.AddressRegister] = vx / 100;
	vx %= 100;
	cpu.Memory[cpu.AddressRegister + 1] = vx / 10;
	vx %= 10;
	cpu.Memory[cpu.AddressRegister + 2] = vx;
}

void StoreRegistersUntillXInMemory(Chip8Cpu& cpu, uint8_t x)
{
	CheckForValidRegister(cpu, x);

	for (int i = 0; i <= x; i++)
	{
		cpu.Memory[cpu.AddressRegister + i] = cpu.GPRegisters[i];
	}
}

void LoadRegistersFromMemoryUntillX(Chip8Cpu& cpu, uint8_t x)
{
	CheckForValidRegister(cpu, x);

	for (int i = 0; i <= x; i++)
	{
		cpu.GPRegisters[i] = cpu.Memory[cpu.AddressRegister + i];
	}
}




