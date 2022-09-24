#pragma once
#include"Chip8Cpu.h"

//00E0
void ClearScreen(Chip8Cpu& cpu);

//00EE
void ReturnFronSubroutine(Chip8Cpu& cpu);

//1NNN
void Jump(Chip8Cpu& cpu, uint16_t);

//2NNN
void CallSubRoutine(Chip8Cpu& cpu, uint16_t);

//3XNN
void SkipIfRegisterEqualValue(Chip8Cpu& cpu, uint16_t opcode);

//4XNN
void SkipIfRegisterNotEqualValue(Chip8Cpu& cpu, uint16_t opcode);

//5XY0
void SkipIfRegisterEqualRegister(Chip8Cpu& cpu, uint16_t opcode);

//6XNN
void SetRegisterByValue(Chip8Cpu& cpu, uint16_t opcode);

//7XNN
void AddValueToRegisterWithoutCarry(Chip8Cpu& cpu, uint16_t opcode);

//8XY0 
void AssignRegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndex);

//8XY1
void SetsRegisterToRegisterORRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndex);

//8XY2
void SetsRegisterToRegisterANDRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndex);

//8XY3
void SetsRegisterToRegisterXORRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndex);

//8XY4
void AddRegisterToRegisterWithCarry(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndex);

//8XY5
void SubtractRegisterFromRegisterWithCarry(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndex);

//8XY6
void ShiftRightBy1RegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t outputRegisterIndedx);

//8XY7
void AssignRegisterXRegisterYMinusRegisterX(Chip8Cpu& cpu, uint8_t xRegisterIndex, uint8_t yRegisterIndedx);

//8XYE
void ShiftLeftBy1RegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t outputRegisterIndedx);

//9XY0
void SkipIfRegisterNotEqualRegister(Chip8Cpu& cpu, uint16_t opcode);

//ANNN
void SetAddressRegister(Chip8Cpu& cpu, uint16_t opcode);

//BNNN
void JumpToFirstRegisterPlusValue(Chip8Cpu& cpu, uint16_t opcode);

//CXNN
void AssignRegisterRandANDValue(Chip8Cpu& cpu, uint16_t opcode);

//DXYN
void DrawSprite(Chip8Cpu& cpu, uint16_t opcode);

//EX9E
void SkipIfKeyInRegisterPressed(Chip8Cpu& cpu, uint8_t registerIndex);

//EXA1
void SkipIfKeyInRegisterNotPressed(Chip8Cpu& cpu, uint8_t registerIndex);

//FX07
void SetRegisterToDelayTimer(Chip8Cpu& cpu, uint8_t registerIndex);

//FX0A
void BlockKeyIsPressedAndAssignItToRegister(Chip8Cpu& cpu, uint8_t registerIndex);

//FX15
void SetDelayTimerToRegister(Chip8Cpu& cpu, uint8_t registerIndex);

//FX18
void SetSoundTimerToRegister(Chip8Cpu& cpu, uint8_t registerIndex);

//FX1E
void AddRegisterToAdressRegister(Chip8Cpu& cpu, uint8_t registerIndex);

//FX29
void SetsAddressRegisterToFontSpriteAtRegister(Chip8Cpu& cpu, uint8_t registerIndex);

//FX33
void StoreASCIIInMemory(Chip8Cpu& cpu, uint8_t registerIndex);

//FX55
void StoreRegistersUntillXInMemory(Chip8Cpu& cpu, uint8_t x);

//FX65
void LoadRegistersFromMemoryUntillX(Chip8Cpu& cpu, uint8_t x);