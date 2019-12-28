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
	_chip8ProgramRunner.ChipCycle();
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
	case 'A':
		input[0xA] = true;
		break;
	case 'B':
		input[0xB] = true;
		break;
	case 'C':
		input[0xC] = true;
		break;
	case 'D':
		input[0xD] = true;
		break;
	case 'E':
		input[0xE] = true;
		break;
	case 'F':
		input[0xF] = true;
		break;
	}

	return input;
}


void Game::ComposeFrame()
{

	const int size = 12;
	auto screenBuffer = _chip8ProgramRunner.GetScreenBuffer();
	for (int i = 0; i < screenBuffer.size(); i++)
	{
		for (int j = 0; j < screenBuffer[i].size(); j++)
		{
			if (screenBuffer[i][j])
			{
				int y = i * size;
				int x = j * size;
				for (int xx = x; xx < x + size; xx++)
				{
					for (int yy = y; yy < y + size; yy++)
					{
						gfx.PutPixel(xx, yy, Colors::White);
					}
				}
			}
			else
			{
				int y = i * size;
				int x = j * size;
				for (int xx = x; xx < x + size; xx++)
				{
					for (int yy = y; yy < y + size; yy++)
					{
						gfx.PutPixel(xx, yy, Colors::Red);
					}
				}
			}
		}
	}
}
