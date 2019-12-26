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

Game::Game(MainWindow& wnd, Chip8ProgramRunner chip8ProgramRunner)
	:
	wnd(wnd),
	gfx(wnd),
	_chip8ProgramRunner(chip8ProgramRunner)
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
}

void Game::ComposeFrame()
{
	auto screenBuffer = _chip8ProgramRunner.GetScreenBuffer();
	for (size_t i = 0; i < screenBuffer.size(); i++)
	{
		for (size_t j = 0; j < screenBuffer[i].size(); j++)
		{
			gfx.PutPixel(j, i, Colors::White);
		}
	}
}
