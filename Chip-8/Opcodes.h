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
void SkipIfRegisterEqualValue(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value);

//4XNN
void SkipIfRegisterNotEqualValue(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value);

//5XY0
void SkipIfRegisterEqualRegister(Chip8Cpu& cpu, uint8_t registerXIndex, uint8_t registerYIndex);

//6XNN
void SetRegisterByValue(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value);

//7XNN
void AddValueToRegisterWithoutCarry(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value);

//8XY0 
void AssignRegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx);

//8XY1
void SetsRegisterToRegisterORRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx);

//8XY2
void SetsRegisterToRegisterANDRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx);

//8XY3
void SetsRegisterToRegisterXORRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx);

//8XY4
void AddRegisterToRegisterWithCarry(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx);

//8XY5
void SubtractRegisterFromRegisterWithCarry(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t sourceRegisterIndedx);

//8XY6
void ShiftRightBy1RegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t outputRegisterIndedx);

//8XY7
void AssignRegisterXRegisterYMinusRegisterX(Chip8Cpu& cpu, uint8_t xRegisterIndex, uint8_t yRegisterIndedx);

//8XYE
void ShiftLeftBy1RegisterToRegister(Chip8Cpu& cpu, uint8_t destRegisterIndex, uint8_t outputRegisterIndedx);

//9XY0
void SkipIfRegisterNotEqualRegister(Chip8Cpu& cpu, uint8_t registerXIndex, uint8_t registerYIndex);

//ANNN
void SetAddressRegister(Chip8Cpu& cpu, uint16_t value);

//BNNN
void JumpToFirstRegisterPlusValue(Chip8Cpu& cpu, uint16_t value);

//CXNN
void AssignRegisterRandANDValue(Chip8Cpu& cpu, uint8_t registerIndex, uint8_t value);

//DXYN
void DrawSprite(Chip8Cpu& cpu, uint8_t xRegisterIndex, uint8_t yRegisterIndex, uint8_t height);