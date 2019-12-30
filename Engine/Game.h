/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include"..\Chip-8\Chip8ProgramRunner.h"

class Game
{
public:
	Game(class MainWindow& wnd, Chip8ProgramRunner chip8ProgramRunner, std::wstring name);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void UpdateInput();
	void ClearInput();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Chip8ProgramRunner _chip8ProgramRunner;
	std::vector<bool> _input;
	unsigned int _frameCounter;
	std::wstring programName;
	static constexpr unsigned int INPUT_FRAME_TIME_UPDATE = 3;
	static constexpr unsigned int OPCODES_PER_FRAME = 10;
	static constexpr unsigned int PIXEL_SIZE = 12;
	static constexpr Color PIXEL_COLOR = Colors::Blue;
	static constexpr Color BACKGROUND_COLOR = Colors::White;
	/********************************/
};