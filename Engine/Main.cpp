/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Main.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/

#include "MainWindow.h"
#include "Game.h"
#include "ChiliException.h"
#include"..\Chip-8\Chip8ProgramRunner.h"
#include"..\Chip-8\OpcodeRunner12BitValue.h"
#include"..\Chip-8\OpcodeRunner4Bit8BitValues.h"
#include"..\Chip-8\OpcodeRunner4BitValue.h"
#include"..\Chip-8\OpcodeRunnerTwo4BitValues.h"
#include"..\Chip-8\OpcodeRunnerThree4BitValues.h"
#include"..\Chip-8\OpcodeRunnerNoValues.h"
#include"..\Chip-8\Opcodes.h"
#include <shellapi.h>

static void AddSprite(Chip8Cpu& cpu, int location, uint8_t sprite[5])
{
	for (int i = 0; i < 5; i++)
	{
		cpu.Memory[i + location] = sprite[i];
	}
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT)
{
	try
	{
		MainWindow wnd(hInst, pArgs);
		try
		{
			uint16_t fontsSpritesAdresses[] = { 0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75 };
			Chip8Cpu chip8Cpu(fontsSpritesAdresses);

			//digits
			uint8_t d0[]{ 0xF0,0x90,0x90,0x90,0xF0 };
			AddSprite(chip8Cpu, 0, d0);
			uint8_t d1[]{ 0x20,0x60,0x20,0x20,0x70 };
			AddSprite(chip8Cpu, 5, d1);
			uint8_t d2[]{ 0xF0,0x10,0xF0,0x80,0xF0 };
			AddSprite(chip8Cpu, 10, d2);
			uint8_t d3[]{ 0xF0,0x10,0xF0,0x10,0xF0 };
			AddSprite(chip8Cpu, 15, d3);
			uint8_t d4[]{ 0x90,0x90,0xF0,0x10,0x10 };
			AddSprite(chip8Cpu, 20, d4);
			uint8_t d5[]{ 0xF0,0x80,0xF0,0x10,0xF0 };
			AddSprite(chip8Cpu, 25, d5);
			uint8_t d6[]{ 0xF0,0x80,0xF0,0x90,0xF0 };
			AddSprite(chip8Cpu, 30, d6);
			uint8_t d7[]{ 0xF0,0x10,0x20,0x40,0x40 };
			AddSprite(chip8Cpu, 35, d7);
			uint8_t d8[]{ 0xF0,0x90,0xF0,0x90,0xF0 };
			AddSprite(chip8Cpu, 40, d8);
			uint8_t d9[]{ 0xF0,0x90,0xF0,0x10,0xF0 };
			AddSprite(chip8Cpu, 45, d9);
			uint8_t dA[]{ 0xF0,0x90,0xF0,0x90,0x90 };
			AddSprite(chip8Cpu, 50, dA);
			uint8_t dB[]{ 0xE0,0x90,0xE0,0x90,0xE0 };
			AddSprite(chip8Cpu, 55, dB);
			uint8_t dC[]{ 0xF0,0x80,0x80,0x80,0xF0 };
			AddSprite(chip8Cpu, 60, dC);
			uint8_t dD[]{ 0xE0,0x90,0xF0,0x90,0xE0 };
			AddSprite(chip8Cpu, 65, dD);
			uint8_t dE[]{ 0xF0,0x80,0xF0,0x80,0xF0 };
			AddSprite(chip8Cpu, 70, dE);
			uint8_t dF[]{ 0xF0,0x80,0xF0,0x80,0x80 };
			AddSprite(chip8Cpu, 75, dF);

			OpcodeTypeParser opcodeTypeParser;

			auto resolverFor0 = [](uint8_t v)
			{
				switch (v)
				{
				case 0:
					return ClearScreen;
				case 0xE:
					return ReturnFronSubroutine;
				default:
					throw std::exception("wired opcode");
				}
			};

			auto resolverFor5 = [](uint8_t v)
			{
				switch (v)
				{
				case 0:
					return SkipIfRegisterEqualRegister;
				default:
					throw std::exception("wired opcode");
				}
			};

			auto resolverFor8 = [](uint8_t v)
			{
				switch (v)
				{
				case 0:
					return AssignRegisterToRegister;
				case 1:
					return SetsRegisterToRegisterORRegister;
				case 2:
					return SetsRegisterToRegisterANDRegister;
				case 3:
					return SetsRegisterToRegisterXORRegister;
				case 4:
					return AddRegisterToRegisterWithCarry;
				case 5:
					return SubtractRegisterFromRegisterWithCarry;
				case 6:
					return ShiftRightBy1RegisterToRegister;
				case 7:
					return AssignRegisterXRegisterYMinusRegisterX;
				case 0xE:
					return ShiftLeftBy1RegisterToRegister;
				default:
					throw std::exception("wired opcode");
				}
			};

			auto resolverFor9 = [](uint8_t v)
			{
				switch (v)
				{
				case 0:
					return SkipIfRegisterNotEqualRegister;
				default:
					throw std::exception("wired opcode");
				}
			};

			auto resolverForE = [](uint8_t v)
			{
				switch (v)
				{
				case 0x9E:
					return SkipIfKeyInRegisterPressed;
				case 0xA1:
					return SkipIfKeyInRegisterNotPressed;
				default:
					throw std::exception("wired opcode");
				}
			};

			auto resolverForF = [](uint8_t v)
			{
				switch (v)
				{
				case 0x7:
					return SetRegisterToDelayTimer;
				case 0xA:
					return BlockKeyIsPressedAndAssignItToRegister;
				case 0x15:
					return SetDelayTimerToRegister;
				case 0x18:
					return SetSoundTimerToRegister;
				case 0x1E:
					return AddRegisterToAdressRegister;
				case 0x29:
					return SetsAddressRegisterToFontSpriteAtRegister;
				case 0x33:
					return StoreASCIIInMemory;
				case 0x55:
					return StoreRegistersUntillXInMemory;
				case 0x65:
					return LoadRegistersFromMemoryUntillX;
				default:
					throw std::exception("wired opcode");
				}
			};

			std::unordered_map<uint8_t, OpcodeRunner&> typeToOpcodeParser{
				{0,*new OpcodeRunnerNoValues(chip8Cpu,resolverFor0)},
				{1,*new OpcodeRunner12BitValue(Jump,chip8Cpu)},
				{2,*new OpcodeRunner12BitValue(CallSubRoutine,chip8Cpu)},
				{3,*new OpcodeRunner4Bit8BitValues(chip8Cpu, SkipIfRegisterEqualValue)},
				{4,*new OpcodeRunner4Bit8BitValues(chip8Cpu, SkipIfRegisterNotEqualValue)},
				{5,*new OpcodeRunnerTwo4BitValues(chip8Cpu,resolverFor5)},
				{6,*new OpcodeRunner4Bit8BitValues(chip8Cpu,SetRegisterByValue)},
				{7,*new OpcodeRunner4Bit8BitValues(chip8Cpu,AddValueToRegisterWithoutCarry)},
				{8,*new OpcodeRunnerTwo4BitValues(chip8Cpu, resolverFor8)},
				{9,*new OpcodeRunnerTwo4BitValues(chip8Cpu, resolverFor9)},
				{0xA,*new OpcodeRunner12BitValue(SetAddressRegister,chip8Cpu)},
				{0xB,*new OpcodeRunner12BitValue(JumpToFirstRegisterPlusValue,chip8Cpu)},
				{0xC,*new OpcodeRunner4Bit8BitValues(chip8Cpu,AssignRegisterRandANDValue)},
				{0xD,*new OpcodeRunnerThree4BitValues(chip8Cpu, DrawSprite)},
				{0xE,*new OpcodeRunner4BitValue(chip8Cpu,resolverForE)},
				{0xF,*new OpcodeRunner4BitValue(chip8Cpu, resolverForF)}
			};

			OpcodeRunnerResolver opcodeRunnerResolver(opcodeTypeParser, typeToOpcodeParser);
			Chip8ProgramRunner programRunner(chip8Cpu, opcodeRunnerResolver);
			int nArgs = 0;
			LPWSTR* args = nullptr;
			args = CommandLineToArgvW(GetCommandLine(), &nArgs);
			std::wstring name = args[1];
			Game theGame(wnd, programRunner, name);
			while (wnd.ProcessMessage())
			{
				theGame.Go();
			}

			for (auto& opcodeRunnerPair : typeToOpcodeParser)
			{
				delete &opcodeRunnerPair.second;
			}

			LocalFree(args);
		}
		catch (const ChiliException& e)
		{
			const std::wstring eMsg = e.GetFullMessage() +
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox(e.GetExceptionType(), eMsg);
		}
		catch (const std::exception& e)
		{
			// need to convert std::exception what() string from narrow to wide string
			const std::string whatStr(e.what());
			const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) +
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox(L"Unhandled STL Exception", eMsg);
		}
		catch (...)
		{
			wnd.ShowMessageBox(L"Unhandled Non-STL Exception",
				L"\n\nException caught at Windows message loop.");
		}
	}
	catch (const ChiliException& e)
	{
		const std::wstring eMsg = e.GetFullMessage() +
			L"\n\nException caught at main window creation.";
		MessageBox(nullptr, eMsg.c_str(), e.GetExceptionType().c_str(), MB_OK);
	}
	catch (const std::exception& e)
	{
		// need to convert std::exception what() string from narrow to wide string
		const std::string whatStr(e.what());
		const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) +
			L"\n\nException caught at main window creation.";
		MessageBox(nullptr, eMsg.c_str(), L"Unhandled STL Exception", MB_OK);
	}
	catch (...)
	{
		MessageBox(nullptr, L"\n\nException caught at main window creation.",
			L"Unhandled Non-STL Exception", MB_OK);
	}


	return 0;
}