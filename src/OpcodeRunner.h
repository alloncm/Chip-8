#pragma once
#include<cstdint>
#include"Chip8Cpu.h"
#include"Opcodes.h"

class OpcodeRunner
{
public:
	OpcodeRunner(Chip8Cpu& cpu) : Cpu(cpu){}

	void operator()(uint16_t opcode)
    {
        uint16_t opcodeType = opcode >> 12;
        switch (opcodeType)
        {
        case 0x0:
            switch (opcode & 0xF)
            {
            case 0x0:
                ClearScreen(Cpu);
                break;
            case 0xE:
                ReturnFronSubroutine(Cpu);
                break;
            default:
                throw "wired opcode";
            }
            break;
        case 0x1:
            Jump(Cpu, opcode);
            break;
        case 0x2:
            CallSubRoutine(Cpu, opcode);
            break;
        case 0x3:
            SkipIfRegisterEqualValue(Cpu, opcode);
            break;
        case 0x4:
            SkipIfRegisterNotEqualValue(Cpu, opcode);
            break;
        case 0x5:
            SkipIfRegisterEqualRegister(Cpu, opcode);
        case 0x6:
            SetRegisterByValue(Cpu, opcode);
            break;
        case 0x7:
            AddValueToRegisterWithoutCarry(Cpu, opcode);
            break;
        case 0x8:
        {
            uint8_t xRegister = (opcode & 0x0F00) >> 8;
            uint8_t yRegister = (opcode & 0x00F0) >> 4;
            switch (opcode & 0x000F)
            {
                case 0x0:
                    AssignRegisterToRegister(Cpu, xRegister, yRegister);
                    break;
                case 0x1:
                    SetsRegisterToRegisterORRegister(Cpu, xRegister, yRegister);
                    break;
                case 0x2:
                    SetsRegisterToRegisterANDRegister(Cpu, xRegister, yRegister);
                    break;
                case 0x3:
                    SetsRegisterToRegisterXORRegister(Cpu, xRegister, yRegister);
                    break;
                case 0x4: 
                    AddRegisterToRegisterWithCarry(Cpu, xRegister, yRegister);
                    break;
                case 0x5: 
                    SubtractRegisterFromRegisterWithCarry(Cpu, xRegister, yRegister);
                    break;
                case 0x6:
                    ShiftRightBy1RegisterToRegister(Cpu, xRegister, yRegister);
                    break;
                case 0x7:
                    AssignRegisterXRegisterYMinusRegisterX(Cpu, xRegister, yRegister);
                    break;
                case 0xE:
                    ShiftLeftBy1RegisterToRegister(Cpu, xRegister, yRegister);
                    break;
                default:
                    break;
            }
            break;
        }
        case 0x9:
            SkipIfRegisterNotEqualRegister(Cpu, opcode);
            break;
        case 0xA:
            SetAddressRegister(Cpu, opcode);
            break;
        case 0xB:
            JumpToFirstRegisterPlusValue(Cpu, opcode);
            break;
        case 0xC:
            AssignRegisterRandANDValue(Cpu, opcode);
            break;
        case 0xD:
            DrawSprite(Cpu, opcode);
            break;
        case 0xE:
        {
            uint8_t reg = (opcode & 0x0F00) >> 8;
            switch (opcode & 0xFF)
            {
            case 0x9E:
                SkipIfKeyInRegisterPressed(Cpu, reg);
                break;
            case 0xA1:
                SkipIfKeyInRegisterNotPressed(Cpu, reg);
                break;
            default:
                break;
            }
            break;
        }
        case 0xF:
        {
            uint8_t reg = (opcode & 0x0F00) >> 8;
            switch (opcode & 0xFF)
            {
            case 0x7:
                SetRegisterToDelayTimer(Cpu, reg);
                break;
            case 0xA:
                BlockKeyIsPressedAndAssignItToRegister(Cpu, reg);
                break;
            case 0x15:
                SetDelayTimerToRegister(Cpu, reg);
                break;
            case 0x18:
                SetSoundTimerToRegister(Cpu, reg);
                break;
            case 0x1E:
                AddRegisterToAdressRegister(Cpu, reg);
                break;
            case 0x29:
                SetsAddressRegisterToFontSpriteAtRegister(Cpu, reg);
                break;
            case 0x33:
                StoreASCIIInMemory(Cpu, reg);
                break;
            case 0x55:
                StoreRegistersUntillXInMemory(Cpu, reg);
                break;
            case 0x65:
                LoadRegistersFromMemoryUntillX(Cpu, reg);
                break;
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
    }
protected:
	Chip8Cpu& Cpu;
};

