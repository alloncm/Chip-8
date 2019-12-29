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
	programName(name)
{
	_chip8ProgramRunner.LoadProgram(programName);
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	for (int i = 0; i < EMULATION_SPEED; i++)
	{
		_chip8ProgramRunner.ChipCycle();
	}

	_chip8ProgramRunner.SetInput(GetInput());
}

std::vector<bool> Game::GetInput()
{
	std::vector<bool> input(16);
	char key = wnd.kbd.ReadChar();
	switch (key)
	{
	case '0':
		input[0] = true;
		break;
	case '1':
		input[1] = true;
		break;
	case '2':
		input[2] = true;
		break;
	case '3':
		input[3] = true;
		break;
	case '4':
		input[4] = true;
		break;
	case '5':
		input[5] = true;
		break;
	case '6':
		input[6] = true;
		break;
	case '7':
		input[7] = true;
		break;
	case '8':
		input[8] = true;
		break;
	case '9':
		input[9] = true;
		break;
	case 'Q':
	case 'q':
		input[0xA] = true;
		break;
	case 'W':
	case 'w':
		input[0xB] = true;
		break;
	case 'E':
	case 'e':
		input[0xC] = true;
		break;
	case 'R':
	case 'r':
		input[0xD] = true;
		break;
	case 'T':
	case 't':
		input[0xE] = true;
		break;
	case 'Y':
	case 'y':
		input[0xF] = true;
		break;
	}

	return input;
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
					Color color = screenBuffer[i][j] ? Colors::White : Colors::Red;
					gfx.PutPixel(tempX, tempY, color);
				}
			}
		}
	}
}
