/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
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

Game::Game(MainWindow& wnd, Chip8ProgramRunner chip8ProgramRunner, std::wstring name)
	:
	wnd(wnd),
	gfx(wnd),
	_chip8ProgramRunner(chip8ProgramRunner),
	programName(name),
	_frameCounter(0)
{
	_chip8ProgramRunner.LoadProgram(programName);
	_input.resize(Chip8Cpu::NUMBER_OF_KEYS);
	ClearInput();
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateInput();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	_chip8ProgramRunner.SetInput(_input);

	for (int i = 0; i < OPCODES_PER_FRAME; i++)
	{
		_chip8ProgramRunner.ChipCycle();
	}
	
	_frameCounter++;
	if (_frameCounter >= INPUT_FRAME_TIME_UPDATE)
	{
		_frameCounter = 0;
		ClearInput();
	}

}

void Game::UpdateInput()
{
	char key = wnd.kbd.ReadChar();
	switch (key)
	{
	case '0':
		_input[0] = true;
		break;
	case '1':
		_input[1] = true;
		break;
	case '2':
		_input[2] = true;
		break;
	case '3':
		_input[3] = true;
		break;
	case '4':
		_input[4] = true;
		break;
	case '5':
		_input[5] = true;
		break;
	case '6':
		_input[6] = true;
		break;
	case '7':
		_input[7] = true;
		break;
	case '8':
		_input[8] = true;
		break;
	case '9':
		_input[9] = true;
		break;
	case 'Q':
	case 'q':
		_input[0xA] = true;
		break;
	case 'W':
	case 'w':
		_input[0xB] = true;
		break;
	case 'E':
	case 'e':
		_input[0xC] = true;
		break;
	case 'R':
	case 'r':
		_input[0xD] = true;
		break;
	case 'T':
	case 't':
		_input[0xE] = true;
		break;
	case 'Y':
	case 'y':
		_input[0xF] = true;
		break;
	}
}

void Game::ClearInput()
{
	for (int i = 0; i < _input.size(); i++)
	{
		_input[i] = false;
	}
}


void Game::ComposeFrame()
{
	auto screenBuffer = _chip8ProgramRunner.GetScreenBuffer();
	for (int i = 0; i < screenBuffer.size(); i++)
	{
		for (int j = 0; j < screenBuffer[i].size(); j++)
		{
			int y = i * PIXEL_SIZE;
			int x = j * PIXEL_SIZE;
			for (int tempX = x; tempX < x + PIXEL_SIZE; tempX++)
			{
				for (int tempY = y; tempY < y + PIXEL_SIZE; tempY++)
				{
					Color color = screenBuffer[i][j] ? PIXEL_COLOR : BACKGROUND_COLOR;
					gfx.PutPixel(tempX, tempY, color);
				}
			}
		}
	}
}
