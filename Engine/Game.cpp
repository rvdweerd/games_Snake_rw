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
#include "Board.h"
#include <chrono>
#include <thread>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(0,0)
{
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
	
	
	/*if (!brd.IsInitialized())
	{
		brd.BoardInit();
	}*/

	if (!brd.IsGameOver())
	{
		//Control direction of snake
		if (wnd.kbd.KeyIsPressed(0x66) &&  brd.GetSnakeDirection() != 2)
		{
			brd.SetSnakeDirection(0);
		}
		if (wnd.kbd.KeyIsPressed(0x64) &&  brd.GetSnakeDirection() != 0)
		{
			brd.SetSnakeDirection(2);
		}
		if (wnd.kbd.KeyIsPressed(0x62) &&  brd.GetSnakeDirection() != 3)
		{
			brd.SetSnakeDirection(1);
		}
		if (wnd.kbd.KeyIsPressed(0x68) &&  brd.GetSnakeDirection() != 1)
		{
			brd.SetSnakeDirection(3);
		}
		if (wnd.kbd.KeyIsPressed(0x65))
		{
			brd.SetSnakeDirection(5);
		}

		//Movement of snake
		//if (!brd.OutOfBounds())  // USE THIS IF YOU WANT TO FORCE A HALT AT THE BORDER
		brd.TestForBorderJump();      // USE THIS IF YOU WANT TO JUMP TO OPPOSITE BORDER AT THE BORDER
		{
			if (brd.GetSnakeDirection() != 5)
			{
				brd.BoardUpdateReduceTail();
				brd.BoardUpdateAdvanceHead();
			}

		}
	}
	else
	{
		brd.SetTileColor(Colors::Red);
	}
}

void Game::ComposeFrame()
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(.1s);
	brd.DrawBoard(gfx);

}


