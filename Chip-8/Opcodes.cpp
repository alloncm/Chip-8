#include"Opcodes.h"
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<string>
#include<exception>
#include<bitset>

static void CheckValidAddress(const Chip8Cpu& cpu, uint16_t address)
{
	if (address > cpu.MEMORY_SIZE)
	{
		throw std::exception("Memory out of bounds address at " + address);
	}
}

static void CheckForValidRegister(const Chip8Cpu& cpu, uint8_t registerIndex)
{
	if (registerIndex >= cpu.NUMBER_OF_REGISTERS)
	{
		throw std::exception("Register is out of bounds " + registerIndex);
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
		throw std::exception("value is bigger than 0xF" + value);
	}
}


void ClearScreen(Chip8Cpu& cpu)
{
	std::memset(cpu.ScreenBuffer, 0, cpu.SCREEN_HIGHT * cpu.SCREEN_WIDTH);
}

void ReturnFronSubroutine(Chip8Cpu& cpu)
{
	uint16_t address = cpu.Pop();
	cpu.ProgramCounter = address;
	cpu.Jumped = true;
}

void Jump(Chip8Cpu& cpu, uint16_t address)
{
	CheckValidAddress(cpu, address);

	cpu.ProgramCounter = address;
	cpu.Jumped = true;
}

void CallSubRoutine(Chip8Cpu& cpu, uint16_t address)
{
	CheckValidAddress(cpu, address);

	cpu.Push(cpu.ProgramCounter);
	cpu.ProgramCounter = address;
	cpu.Jumped = true;
}

void SkipIfRegisterEqualValue(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value)
{
	CheckForValidRegister(cpu, registerIndex);

	SkipIfTrue(cpu, cpu.GPRegisters[registerIndex] == value);
}

void SkipIfRegisterNotEqualValue(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value)
{
	CheckForValidRegister(cpu, registerIndex);

	SkipIfTrue(cpu, cpu.GPRegisters[registerIndex] != value);
}

void SkipIfRegisterEqualRegister(Chip8Cpu& cpu, uint8_t registerXIndex, uint8_t registerYIndex)
{
	CheckForValidRegister(cpu, registerXIndex);
	CheckForValidRegister(cpu, registerYIndex);

	SkipIfTrue(cpu, cpu.GPRegisters[registerXIndex] == cpu.GPRegisters[registerYIndex]);
}

void SetRegisterByValue(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value)
{
	CheckForValidRegister(cpu, registerIndex);
	cpu.GPRegisters[registerIndex] = value;
}

void AddValueToRegisterWithoutCarry(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value)
{
	CheckForValidRegister(cpu, registerIndex);
	cpu.GPRegisters[registerIndex] += value;
}

void AssignRegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, sourceRegisterIndedx);

	cpu.GPRegisters[destRegisterIndex] = cpu.GPRegisters[sourceRegisterIndedx];
}

void SetsRegisterToRegisterORRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx)
{
	CheckForValidRegister(cpu, destRegisterIndex);
	CheckForValidRegister(cpu, sourceRegisterIndedx);

	cpu.GPRegisters[destRegisterIndex] |= cpu.GPRegisters[sourceRegisterIndedx];
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

void SkipIfRegisterNotEqualRegister(Chip8Cpu& cpu, uint8_t registerXIndex, uint8_t registerYIndex)
{
	CheckForValidRegister(cpu, registerXIndex);
	CheckForValidRegister(cpu, registerYIndex);

	SkipIfTrue(cpu, cpu.GPRegisters[registerXIndex] != cpu.GPRegisters[registerYIndex]);
}

void SetAddressRegister(Chip8Cpu& cpu, uint16_t value)
{
	CheckValidAddress(cpu, value);

	cpu.AddressRegister = value;
}

void JumpToFirstRegisterPlusValue(Chip8Cpu& cpu, uint16_t value)
{
	uint16_t address = cpu.GPRegisters[0] + value;
	CheckValidAddress(cpu, address);

	cpu.ProgramCounter = address;
	cpu.Jumped = true;
}

void AssignRegisterRandANDValue(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value)
{
	CheckForValidRegister(cpu, registerIndex);

	srand(time(NULL));
	uint8_t randomNumber = rand() % UINT8_MAX;
	cpu.GPRegisters[registerIndex] = randomNumber & value;
}

void DrawSprite(Chip8Cpu& cpu, uint8_t xRegisterIndex, uint8_t yRegisterIndex, uint8_t height)
{
	CheckForValidRegister(cpu, xRegisterIndex);
	CheckForValidRegister(cpu, yRegisterIndex);
	if (height > 0xF)
	{
		throw std::exception("height is bigger than 0xF" + height);
	}

	bool flliped = false;
	uint16_t addressTemp = cpu.AddressRegister;
	for (int i = 0; i < height; i++)
	{
		uint8_t v = cpu.Memory[addressTemp];
		addressTemp++;
		std::bitset<8> bits(v);
		for (int j = 0; j < cpu.SPRITE_WIDTH; j++)
		{
			int x = j + cpu.GPRegisters[xRegisterIndex];
			int y = i + cpu.GPRegisters[yRegisterIndex];
			if (cpu.ScreenBuffer[cpu.SCREEN_WIDTH * y + x] != bits[7-j])
			{
				cpu.ScreenBuffer[cpu.SCREEN_WIDTH * y + x] = bits[7-j];
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
	cpu.Block();
	bool found = false;
	uint8_t i = 0;
	while (i < cpu.NUMBER_OF_KEYS && !found)
	{
		if (cpu.Keys[i])
		{
			found = true;
		}
		else
		{
			i++;
		}
	}

	cpu.GPRegisters[registerIndex] = i;
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




